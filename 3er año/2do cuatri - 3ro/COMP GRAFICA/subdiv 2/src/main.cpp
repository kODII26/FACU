//#include <algorithm>
#include <stdexcept>
#include <vector>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Model.hpp"
#include "Window.hpp"
#include "Callbacks.hpp"
#include "Debug.hpp"
#include "Shaders.hpp"
#include "SubDivMesh.hpp"
#include "SubDivMeshRenderer.hpp"

#define VERSION 20251006

// models and settings
std::vector<std::string> models_names = { "cubo", "icosahedron", "plano", "suzanne", "star" };
int current_model = 0;
bool fill = true, nodes = true, wireframe = true, smooth = false, 
	reload_mesh = true, mesh_modified = false;

// extraa callbacks
void keyboardCallback(GLFWwindow* glfw_win, int key, int scancode, int action, int mods);

SubDivMesh mesh;
void subdivide(SubDivMesh &mesh);

int main() {
	
	// initialize window and setup callbacks
	Window window(win_width,win_height,"CG Demo");
	setCommonCallbacks(window);
	glfwSetKeyCallback(window, keyboardCallback);
	view_fov = 60.f;
	
	// setup OpenGL state and load shaders
	glEnable(GL_DEPTH_TEST); glDepthFunc(GL_LESS); 
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.8f,0.8f,0.9f,1.f);
	Shader shader_flat("shaders/flat"),
		shader_smooth("shaders/smooth"),
		shader_wireframe("shaders/wireframe");
	SubDivMeshRenderer renderer;
	
	// main loop
	Material material;
	material.ka = material.kd = glm::vec3{.8f,.4f,.4f};
	material.ks = glm::vec3{.5f,.5f,.5f};
	material.shininess = 50.f;
	
	FrameTimer timer;
	do {
		
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		
		if (reload_mesh) {
			mesh = SubDivMesh("models/"+models_names[current_model]+".dat");
			reload_mesh = false; mesh_modified = true;
		}
		if (mesh_modified) {
			renderer = makeRenderer(mesh,false);
			mesh_modified = false;
		}
		
		if (nodes) {
			shader_wireframe.use();
			setMatrixes(shader_wireframe);
			renderer.drawPoints(shader_wireframe);
		}
		
		if (wireframe) {
			shader_wireframe.use();
			setMatrixes(shader_wireframe);
			renderer.drawLines(shader_wireframe);
		}
		
		if (fill) {
			Shader &shader = smooth ? shader_smooth : shader_flat;
			shader.use();
			setMatrixes(shader);
			shader.setLight(glm::vec4{2.f,1.f,5.f,0.f}, glm::vec3{1.f,1.f,1.f}, 0.25f);
			shader.setMaterial(material);
			renderer.drawTriangles(shader);
		}
		
		// settings sub-window
		window.ImGuiDialog("CG Example",[&](){
			if (ImGui::Combo(".dat (O)", &current_model,models_names)) reload_mesh = true;
			ImGui::Checkbox("Fill (F)",&fill);
			ImGui::Checkbox("Wireframe (W)",&wireframe);
			ImGui::Checkbox("Nodes (N)",&nodes);
			ImGui::Checkbox("Smooth Shading (S)",&smooth);
			if (ImGui::Button("Subdivide (D)")) { subdivide(mesh); mesh_modified = true; }
			if (ImGui::Button("Reset (R)")) reload_mesh = true;
			ImGui::Text("Nodes: %i, Elements: %i",mesh.n.size(),mesh.e.size());
		});
		
		// finish frame
		window.finishFrame();
		
	} while( glfwGetKey(window,GLFW_KEY_ESCAPE)!=GLFW_PRESS && !glfwWindowShouldClose(window) );
}

void keyboardCallback(GLFWwindow* glfw_win, int key, int scancode, int action, int mods) {
	if (action==GLFW_PRESS) {
		switch (key) {
		case 'D': subdivide(mesh); mesh_modified = true; break;
		case 'F': fill = !fill; break;
		case 'N': nodes = !nodes; break;
		case 'W': wireframe = !wireframe; break;
		case 'S': smooth = !smooth; break;
		case 'R': reload_mesh=true; break;
		case 'O': case 'M': current_model = (current_model+1)%models_names.size(); reload_mesh = true; break;
		}
	}
}

// La struct Arista guarda los dos indices de nodos de una arista
// Siempre pone primero el menor indice, para facilitar la búsqueda en 
//lista ordenada;
//    es para usar con el Mapa de mas abajo, para asociar un nodo nuevo 
//a una arista vieja
struct Arista {
	int n[2];
	Arista(int n1, int n2) {
		n[0]=n1; n[1]=n2;
		if (n[0]>n[1]) std::swap(n[0],n[1]);
	}
	Arista(Elemento &e, int i) { // i-esima arista de un elemento
		n[0]=e[i]; n[1]=e[i+1];
		if (n[0]>n[1]) std::swap(n[0],n[1]); 
	}
	const bool operator<(const Arista &a) const {
		return (n[0]<a.n[0]||(n[0]==a.n[0]&&n[1]<a.n[1]));
	}
};

// Mapa sirve para guardar una asociación entre una arista y un indice de 
//nodo (que no es de la arista)
using Mapa = std::map<Arista,int>;


void subdivide(SubDivMesh &mesh) {
	int cantidad_nodos_iniciales = mesh.n.size();
	/// @@@@@: Implementar Catmull-Clark... lineamientos:
	//  Los nodos originales estan en las posiciones 0 a #n-1 de m.n,
	//  Los elementos orignales estan en las posiciones 0 a #e-1 de m.e
	//  1) Crear centroides de cada elemento 
	//	Por cada elemento, agregar el centroide (nuevos nodos: #n a #n+#e-1)
	//	std::map<int,std::vector<int>> nodo_centroides;
	/* Para cada cara (triángulo o cuadrilátero):
	1. Sumar las posiciones de todos sus vértices
	2. Dividir por la cantidad de vértices (3 o 4)
	3. Agregar el nuevo nodo centroide a la malla
	*/
	for(size_t j=0;j<mesh.e.size();j++) {
		Elemento elemento = mesh.e[j];
		glm::vec3 centroide = glm::vec3(0.f);
		
		// Calcular el centroide promediando las posiciones de los nodos
		for (int i = 0; i < elemento.nv; i++) {
			centroide += mesh.n[elemento.n[i]].p;  // Accede a la posición del nodo
			
			//			nodo_centroides[elemento.n[i]].push_back(mesh.n.size());
			
		}
		centroide /= elemento.nv;  // Promedio para obtener el centroide
		//		 Crear el nuevo nodo con el centroide calculado
		Nodo nuevo_nodo(centroide);
		
		mesh.n.push_back(nuevo_nodo);  // Agregar el nuevo nodo a la lista de nodos
	}
	
	
	
	//  2) Crear puntos en las aristas 
	//		Por cada arista de cada cara, agregar un pto en el medio que es
	//      promedio de los vertices de la arista y los centroides de las caras 
	//      adyacentes. Aca hay que usar los elementos vecinos.
	//      En los bordes, cuando no hay vecinos, es simplemente el promedio de los 
	//      vertices de la arista
	//      Hay que evitar procesar dos veces la misma arista (como?)
	//      Mas adelante vamos a necesitar determinar cual punto agregamos en cada
	//      arista, y ya que no se pueden relacionar los indices con una formula simple
	//      se sugiere usar Mapa como estructura auxiliar
	std::map<Arista,int> m; // asocia cada arista a su nodo correspondiente		
	for(size_t j=0;j<mesh.e.size();j++)  // recorro todas las caras
	{  // Para cada elemento (cara)
		Elemento elemento = mesh.e[j]; // elemento en el que estoy parado
		for (int i = 0; i < elemento.nv; i++) { // recorro cada vertice/nodo
			Arista ar(-1,-1); // arista aux
			// elemento.n[i] devuelve el indice del Nodo
			// me lo guardo en el mapa
			if(i == elemento.nv-1) {Arista ar2(elemento.n[0],elemento.n[i]); ar = ar2;} 
			// si es la ultima arista la "uno" con el primer nodo
			// en caso contrario es el nodo siguiente
			else {Arista ar2(elemento.n[i],elemento.n[i+1]); ar = ar2;} 
			if(m.find(ar) == m.end() ) { // si esta arista NO esta en el mapa
				m[ar] = mesh.n.size(); // 
				if ( elemento.v[i] == -1 ) { // caso frontera (no tiene vecino)
					// nuevo punto promedio simple de 2 puntos
					// Acceso a los nodos de la arista
					int nodo1 = ar.n[0]; // el indice del nodo1
					int nodo2 = ar.n[1]; // el indice del nodo2
					//Calcula el punto medio de los nodos en la malla
					glm::vec3 mitad = glm::vec3(0.f);
					mitad += mesh.n[nodo1].p + mesh.n[nodo2].p;
					mitad /= 2;
					// Crea un nuevo nodo y lo agrega a la malla
					Nodo nuevo_nodo(mitad);
					mesh.n.push_back(nuevo_nodo);
				}
				else // caso NO frontera (comparte la arista con otra cara)
				{	// nuevo punto= promedio de los 2 vertices de la aritsa, el centroide de esta cara, el centroide de la cara vecina
					glm::vec3 centroide_1 =  mesh.n[cantidad_nodos_iniciales +j].p;
					//					std::cout << "malla ACTUAL [" << j <<"] nodo:" << 	cantidad_nodos_iniciales + j  << " x=" << centroide_1.x << " y=" << centroide_1.y << " z=" << centroide_1.z << std::endl;
					glm::vec3 centroide_2 = mesh.n[cantidad_nodos_iniciales  +elemento.v[i] ].p;
					
					glm::vec3 promedio = glm::vec3(0.f);
					promedio+= centroide_1 + centroide_2 + mesh.n[ar.n[0]].p + mesh.n[ar.n[1]].p;
					promedio/=4.f;
					
					Nodo nuevo_nodo(promedio);
					
					
					
					mesh.n.push_back(nuevo_nodo);
				}
			}
		}
	}
	
	
	//  3) Armar los elementos nuevos
	//Catmull-Clark convierte cada elemento original en múltiples cuadriláteros:
	//	Triángulo (3 vertices -> 3 quads
	//	Cuadrilátero (4 vertices -> 4 quads
	//      Los quads se dividen en 4, (uno reemplaza al original, los otros 3 se agregan)
	//      Los triangulos se dividen en 3, (uno reemplaza al original, los otros 2 se agregan)
	//      Para encontrar los nodos de las aristas usar el mapa que armaron en el paso 2
	//      Ordenar los nodos de todos los elementos nuevos con un mismo criterio (por ej, 
	//      siempre poner primero al centroide del elemento), para simplificar el paso 4.
	std::vector<Elemento> elementos_nuevos;  // Almaceno elementos nuevos (los quads)
	for (int i = 0, ne=mesh.e.size(); i < ne; i++) { 
		Elemento elemento_actual = mesh.e[i]; // toma el cuadrado
		int indice_centroide = cantidad_nodos_iniciales+i; // obtiene su centroide, calc en paso 1
		
		
		for (int j = 0; j < elemento_actual.nv; ++j) {  // Crea 4 o 3 quads
			// Para cada vértice, 
			//Identifica las dos aristas que tocan ese vértice
			// Obtiene los puntos de arista que obtuvimos en el p2
			// Crea un nuevo cuad conectando El centroide del elemento original, El punto de una arista , Un vertice original, el punto de la siguiente arista
			
			Arista anterior(-1,-1);
			if(j == 0 ) {
				Arista ar(elemento_actual.n[elemento_actual.nv-1],elemento_actual.n[0]);
				anterior=ar;
			}
			else { 
				Arista ar(elemento_actual.n[j],elemento_actual.n[j-1]);
				anterior=ar;
			}
			Arista actual(-1,-1);
			if(j == elemento_actual.nv-1 ) {
				Arista ar(elemento_actual.n[0],elemento_actual.n[j]);
				actual=ar;
			}
			else { 
				Arista ar(elemento_actual.n[j],elemento_actual.n[j+1]);
				actual=ar;
			}
			
			if(j!=0){
				
				mesh.agregarElemento(indice_centroide, m[anterior],elemento_actual.n[j], m[actual]);;
			}
			else {
				mesh.reemplazarElemento(i,indice_centroide, m[anterior],elemento_actual.n[j], m[actual]);
			}
		}
	}
	mesh.makeVecinos();
	//  4) Reposicionar los nodos originales
	//		Calcular las nuevas posiciones de los nodos originales 
	//      Para nodos interiores: (4r-f+(n-3)p)/n
	//         f=promedio de nodos interiores de las caras (los agregados en el paso 1)
	//         r=promedio de los pts medios de las aristas (los agregados en el paso 2)
	//         p=posicion del nodo original
	//         n=cantidad de elementos para ese nodo
	//      Para nodos del borde: (r+p)/2
	//         r=promedio de los dos pts medios de las aristas
	//         p=posicion del nodo original
	//	std::cout << nodo_centroides.size();
	for(int i=0;i<cantidad_nodos_iniciales;i++) { 
		// posicion del nodo original
		glm::vec3 p = mesh.n[i].p;  
		// cantidad de caras en las q aparece este nodo
		int n = mesh.n[i].e.size();
		// r = promedio de los puntos medios de las aristas
		// que contienen a este punto
		glm::vec3 r = glm::vec3(0.f);
		int cant_aristas = 0;
		for( std::map<Arista,int>::iterator it=m.begin(); it!=m.end(); ++it ) { 
			int pos = it->second; // valor
			Arista ar = it->first;		// clave
			if( ar.n[0] == i or ar.n[1] == i ) {
				r += mesh.n[pos].p;
				cant_aristas++;
			}
		}
		r/=cant_aristas;
		
		
		
		glm::vec3 f = glm::vec3(0.f);
		
		for(int j=0;j<mesh.n[i].e.size();j++) { 
			
			int pos_elemento = mesh.n[i].e[j]; // pos del elemento
			//			std::cout << "POSELEM: "<<i << " "<<pos_elemento << std::endl;
			int pos_centroide = mesh.e[pos_elemento].n[0];
			
			
			f+=mesh.n[pos_centroide].p;
		}
		f/=mesh.n[i].e.size();
		
		
		glm::vec3 r2 = glm::vec3(0.f);
		for( std::map<Arista,int>::iterator it=m.begin(); it!=m.end(); ++it ) { 
			Arista ar = it->first;	
			int pos = it->second;
			
				if( ar.n[0] == i or ar.n[1] == i ) {
					if(mesh.n[it->second].es_frontera  == true) {
						r2 += mesh.n[pos].p;
					}
				}
				
			
			
		}
		r2/=2;
		if(mesh.n[i].es_frontera == false) {
			/// n = cantidad de elementos para ese nodo
			
			
			/// formula
			glm::vec3 pos_nueva = glm::vec3(0.f);
			pos_nueva =  (4.f*r) - f + ( (n-3.f) * p);
			pos_nueva /=n;
			mesh.n[i].p = pos_nueva;
		}
		else {
			
			
			
			glm::vec3 pos_nueva = glm::vec3(0.f);
			pos_nueva = (r2+p) /2.f;
			mesh.n[i].p = pos_nueva;
		}
	}
	

	//      Ojo: en el paso 3 cambio toda la SubDivMesh, analizar donde quedan en los nuevos 
	//      elementos (¿de que tipo son?) los nodos de las caras y los de las aristas 
	//      que se agregaron antes.
	// tips:
	//   no es necesario cambiar ni agregar nada fuera de este método, (con Mapa como 
	//     estructura auxiliar alcanza)
	//   sugerencia: probar primero usando el cubo (es cerrado y solo tiene quads)
	//               despues usando la piramide (tambien cerrada, y solo triangulos)
	//               despues el ejemplo plano (para ver que pasa en los bordes)
	//               finalmente el mono (tiene mezcla y elementos sin vecinos)
	//   repaso de como usar un mapa:
	//     para asociar un indice (i) de nodo a una arista (n1-n2): elmapa[Arista(n1,n2)]=i;
	//     para saber si hay un indice asociado a una arista:  ¿elmapa.find(Arista(n1,n2))!=elmapa.end()?
	//     para recuperar el indice (en j) asociado a una arista: int j=elmapa[Arista(n1,n2)];
	
	
	// Esta llamada valida si la estructura de datos quedó consistente (si todos los
	// índices están dentro del rango válido, y si son correctas las relaciones
	// entre los .n de los elementos y los .e de los nodos). Mantener al final de
	// esta función para ver que la subdivisión implementada no rompa esos invariantes.
	mesh.verificarIntegridad();
	
}








