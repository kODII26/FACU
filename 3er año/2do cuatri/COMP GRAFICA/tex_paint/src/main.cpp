#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <string>
#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Model.hpp"
#include "Window.hpp"
#include "Callbacks.hpp"
#include "Debug.hpp"
#include "Shaders.hpp"

#define VERSION 20250901

Window main_window; // ventana principal: muestra el modelo en 3d sobre el que se pinta
Window aux_window;	// ventana auxiliar que muestra la textura

void drawMain();				// dibuja el modelo "normalmente" para la ventana principal
void drawBack();				// dibuja el modelo con un shader alternativo para convertir coords de la ventana a coords de textura
void drawAux();					// dibuja la textura en la ventana auxiliar
void drawImGui(Window &window); // settings sub-window

float radius = 5;						// radio del "pincel" con el que pintamos en la textura
glm::vec4 color = {0.f, 0.f, 0.f, 1.f}; // color actual con el que se pinta en la textura

Texture texture; // textura (compartida por ambas ventanas)
Image image;	 // imagen (para la textura, Image est? en RAM, Texture la env?a a GPU)

Model model_chookity; // el objeto a pintar, para renderizar en la ventan principal
Model model_aux;	  // un quad para cubrir la ventana auxiliar y mostrar la textura

Shader shader_main; // shader para el objeto principal (drawMain)
Shader shader_back; // shader para el renderizado de coordenadas de textura (drawBack)
Shader shader_aux;	// shader para la ventana auxiliar (drawTexture)

// callbacks del mouse y auxiliares para los callbacks
enum class MouseAction
{
	None,
	ManipulateView,
	Draw
};
MouseAction mouse_action = MouseAction::None; // qu? hacer en el callback del motion si el bot?n del mouse est? apretado
void mainMouseMoveCallback(GLFWwindow *window, double xpos, double ypos);
void mainMouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
void auxMouseMoveCallback(GLFWwindow *window, double xpos, double ypos);
void auxMouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

/// 
// Variables para tracking del mouse
double last_x = 0, last_y = 0;
bool show_back_buffer = false;

// Funciones auxiliares para rasterizaci?n
void drawPoint(int x, int y, float radius, const glm::vec4 &color);
void drawLine(int x1, int y1, int x2, int y2, float width, const glm::vec4 &color);
void drawCircle(int center_x, int center_y, float radius, const glm::vec4 &color);
glm::vec2 screenToTextureCoords(double x, double y, GLFWwindow *window);
///

int main()
{

	// main window (3D view)
	main_window = Window(800, 600, "Main View", true);
	glfwSetCursorPosCallback(main_window, mainMouseMoveCallback);
	glfwSetMouseButtonCallback(main_window, mainMouseButtonCallback);
	main_window.getCamera().model_angle = 2.5;

	glClearColor(1.f, 1.f, 1.f, 1.f);
	shader_main = Shader("shaders/main");
	///
	shader_back = Shader("shaders/back");
	///
	image = Image("models/chookity.png", true);
	texture = Texture(image);

	model_chookity = Model::loadSingle("models/chookity", Model::fNoTextures);

	// aux window (texture image)
	aux_window = Window(512, 512, "Texture", true, main_window);
	glfwSetCursorPosCallback(aux_window, auxMouseMoveCallback);
	glfwSetMouseButtonCallback(aux_window, auxMouseButtonCallback);

	model_aux = Model::loadSingle("models/texquad", Model::fNoTextures);
	shader_aux = Shader("shaders/quad");

	// main loop
	do
	{
		glfwPollEvents();

		glfwMakeContextCurrent(main_window);
		///
		if (show_back_buffer)
		{
			drawBack();
		}
		else
		{
			drawMain();
		}
		///
		drawImGui(main_window);
		glFinish();
		glfwSwapBuffers(main_window);

		glfwMakeContextCurrent(aux_window);
		drawAux();
		drawImGui(aux_window);
		glFinish();
		glfwSwapBuffers(aux_window);

	} while ((not glfwWindowShouldClose(main_window)) and (not glfwWindowShouldClose(aux_window)));
}

// ===== pasos del renderizado =====

void drawMain()
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	texture.bind();
	shader_main.use();
	setMatrixes(main_window, shader_main);
	shader_main.setLight(glm::vec4{-1.f, 1.f, 4.f, 1.f}, glm::vec3{1.f, 1.f, 1.f}, 0.35f);
	shader_main.setMaterial(model_chookity.material);
	shader_main.setBuffers(model_chookity.buffers);
	model_chookity.buffers.draw();
}

void drawAux()
{
	glDisable(GL_DEPTH_TEST);
	texture.bind();
	shader_aux.use();
	shader_aux.setMatrixes(glm::mat4{1.f}, glm::mat4{1.f}, glm::mat4{1.f});
	shader_aux.setBuffers(model_aux.buffers);
	model_aux.buffers.draw();
}

void drawBack()
{
	glfwMakeContextCurrent(main_window);
	glDisable(GL_MULTISAMPLE);
	
	/// @ToDo: Parte 2: renderizar el modelo en 3d con un nuevo shader de forma
	///                 que queden las coordenadas de textura de cada fragmento
	///                 en el back-buffer de color
	
	///
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shader_back.use();
	setMatrixes(main_window, shader_back);
	shader_back.setBuffers(model_chookity.buffers);
	model_chookity.buffers.draw();
	///
	
	glEnable(GL_MULTISAMPLE);
	glFlush();
	glFinish();
}



void drawImGui(Window &window)
{
	if (!glfwGetWindowAttrib(window, GLFW_FOCUSED))
		return;
	// settings sub-window
	window.ImGuiDialog("Settings", [&]()
					   {
		ImGui::SliderFloat("Radius",&radius,1,50);
		ImGui::ColorEdit4("Color",&(color[0]),0);
		
		static std::vector<std::pair<const char *, ImVec4>> pallete = { // colores predefindos
			{"white" , {1.f,1.f,1.f,1.f}},
			{"pink"  , {0.749f,0.49f,0.498f,1.f}},
			{"yellow", {0.965f,0.729f,0.106f,1.f}},
			{"black" , {0.f,0.f,0.f,1.f}} };
		
		ImGui::Text("Pallete:");
		for (auto &p : pallete) {
			ImGui::SameLine();
			if (ImGui::ColorButton(p.first, p.second))
				color[0] = p.second.x, color[1] = p.second.y, color[2] = p.second.z;
		}
		
		if (ImGui::Button("Reload Image")) {
			image = Image("models/chookity.png",true);
			texture.update(image);
		}
		///
		if (&window == &main_window) {
			ImGui::Checkbox("Show Tex Coords", &show_back_buffer);
		} });
		///
}

// ===== callbacks de la ventana auxiliar (textura) =====

void auxMouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
	if (ImGui::GetIO().WantCaptureMouse)
		return;
	if (action == GLFW_PRESS)
	{
		mouse_action = MouseAction::Draw;

		/// @ToDo: Parte 1: pintar un punto de radio "radius" en la imagen
		///                 "image" que se usa como textura

		// Obtener coordenadas del mouse
		glfwGetCursorPos(window, &last_x, &last_y);

		// Convertir coordenadas de pantalla a coordenadas de textura
		glm::vec2 tex_coords = screenToTextureCoords(last_x, last_y, window);

		// Pintar un punto en la imagen
		drawPoint(tex_coords.x, tex_coords.y, radius, color);

		// Actualizar la textura en la GPU
		texture.update(image);
	}
	else
	{
		mouse_action = MouseAction::None;
	}
}

void auxMouseMoveCallback(GLFWwindow *window, double xpos, double ypos)
{
	if (mouse_action != MouseAction::Draw)
		return;

	/// @ToDo: Parte 1: pintar un segmento de ancho "2*radius" en la imagen
	///                 "image" que se usa como textura

	// Convertir coordenadas actuales y anteriores a coordenadas de textura
	glm::vec2 current_tex_coords = screenToTextureCoords(last_x, last_y, window);
	glm::vec2 last_tex_coords = screenToTextureCoords(xpos, ypos, window);

	// Pintar una l?nea entre los dos puntos
	drawLine(last_tex_coords.x, last_tex_coords.y,
			 current_tex_coords.x, current_tex_coords.y,
			 radius * 2.0f, color);

	// Actualizar la textura en la GPU
	texture.update(image);

	// Guardar las coordenadas actuales para el siguiente frame
	last_x = xpos;
	last_y = ypos;
}

// ===== callbacks de la ventana principal (vista 3D) =====

auto decodeUV (const float* rgba, float& u, float& v)
{
	float u_hi = rgba[0];
	float u_lo = rgba[1];
	float v_hi = rgba[2];
	float v_lo = rgba[3];
	
	u = u_hi + (u_lo / 256.0f);
	v = v_hi + (v_lo / 256.0f);
	
	// Clamp (evitar 1.0 exacto que podría dar texel fuera de rango)
	u = glm::clamp(u, 0.0f, 1.0f);
	v = glm::clamp(v, 0.0f, 1.0f);
	return glm::vec2(u,v);
}

void mainMouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
	if (ImGui::GetIO().WantCaptureMouse)
		return;
	if (action == GLFW_PRESS)
	{
		if (mods != 0 or button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			mouse_action = MouseAction::ManipulateView;
			common_callbacks::mouseButtonCallback(window, GLFW_MOUSE_BUTTON_LEFT, action, mods);
			return;
		}

		mouse_action = MouseAction::Draw;

		/// @ToDo: Parte 2: pintar un punto de radio "radius" en la imagen
		///                 "image" que se usa como textura
		glfwGetCursorPos(window, &last_x, &last_y);

		// Asegurar que el contexto de la ventana principal estÃ© activo
		glfwMakeContextCurrent(main_window);

		// Renderizar el modelo con coordenadas de textura como color
		drawBack();
		glFlush();
		glFinish();

		// Convertir coord. del cursor (en coords de ventana) a pixels del framebuffer (DPI scaling)
		int ww = 0, wh = 0;
		glfwGetWindowSize(window, &ww, &wh);
		BufferSize bs = getBufferSize(window);
		double sx = (ww > 0) ? (double)bs.width / (double)ww : 1.0;
		double sy = (wh > 0) ? (double)bs.height / (double)wh : 1.0;
		int win_x = glm::clamp((int)std::floor(last_x * sx), 0, bs.width - 1);
		int win_y = glm::clamp(bs.height - 1 - (int)std::floor(last_y * sy), 0, bs.height - 1);

		float depth;
		// Leer profundidad desde el depth buffer (glReadBuffer no afecta la lectura de depth)
		glReadPixels(win_x, win_y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

		// Debug temporal - mostrar valores
		printf("Click en (%d,%d) - Depth: %.6f\n", win_x, win_y, depth);

		if (depth < 1.0f)
		{
			// Leer el color directamente del framebuffer actual
			float rgba[4];
			glReadBuffer(GL_BACK);
			glReadPixels(win_x, win_y, 1, 1, GL_RGBA, GL_FLOAT, rgba);
			
			// Decodificar U y V (16 bits efectivos por componente: 8 bits en hi + 8 bits en lo)
			// v = hi + lo/256.0   con hi = floor(v*256)/256 y lo = fract(v*256) en el shader
			float u,v;
			decodeUV(rgba, u, v);
			
			// Clampeo (por ruido numérico); opcionalmente evitá el 1.0 exacto para no caer fuera de rango
			u = glm::clamp(u, 0.0f, 1.0f);
			v = glm::clamp(v, 0.0f, 1.0f);
			
			// Pasar a coordenadas de texel (floor para que u=1.0 no salte fuera)
			int tex_w = image.GetWidth();
			int tex_h = image.GetHeight();
			
			int tex_x = std::min(tex_w - 1, (int)std::floor(u * tex_w));
			int tex_y = std::min(tex_h - 1, (int)std::floor(v * tex_h));

			drawPoint(tex_x, tex_y, radius, color);
			texture.update(image);
			printf("Pintado!\n");
			
		}
		else
		{
			printf("Click fuera del model (depth = 1.0)\n");
		}
	}
	else
	{
		if (mouse_action == MouseAction::ManipulateView)
			common_callbacks::mouseButtonCallback(window, GLFW_MOUSE_BUTTON_LEFT, action, mods);
		mouse_action = MouseAction::None;
	}
}


void mainMouseMoveCallback(GLFWwindow *window, double xpos, double ypos)
{
	if (mouse_action != MouseAction::Draw)
	{
		if (mouse_action == MouseAction::ManipulateView) ;
		common_callbacks::mouseMoveCallback(window, xpos, ypos);
		return;
	}
	glfwMakeContextCurrent(main_window);
	drawBack();
	glFlush();
	glFinish();
	
	// Ventana -> framebuffer 
	int ww = 0, wh = 0;
	glfwGetWindowSize(window, &ww, &wh);
	BufferSize bs = getBufferSize(window);
	double sx = (ww > 0) ? (double)bs.width  / (double)ww : 1.0;
	double sy = (wh > 0) ? (double)bs.height / (double)wh : 1.0;
	
	// Punto anterior en framebuffer
	int last_win_x = glm::clamp((int)std::floor(last_x * sx), 0, bs.width  - 1);
	int last_win_y = glm::clamp(bs.height - 1 - (int)std::floor(last_y * sy), 0, bs.height - 1);
	
	float last_depth = 1.0f;
	glReadPixels(last_win_x, last_win_y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &last_depth);
	
	// Punto actual en framebuffer
	int current_win_x = glm::clamp((int)std::floor(xpos * sx), 0, bs.width  - 1);
	int current_win_y = glm::clamp(bs.height - 1 - (int)std::floor(ypos * sy), 0, bs.height - 1);
	
	float current_depth = 1.0f;
	glReadPixels(current_win_x, current_win_y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &current_depth);
	
	if (last_depth < 1.0f && current_depth < 1.0f)
	{
		// Leer RGBA codificado (UV hi/lo) en ambos puntos
		float last_rgba[4], curr_rgba[4];
		glReadBuffer(GL_BACK);
		glReadPixels(last_win_x,    last_win_y,    1, 1, GL_RGBA, GL_FLOAT, last_rgba);
		glReadPixels(current_win_x, current_win_y, 1, 1, GL_RGBA, GL_FLOAT, curr_rgba);
		
		// Decodificar U y V con 16 bits efectivos: u = u_hi + u_lo/256
		float last_u, last_v, curr_u, curr_v;
		decodeUV(last_rgba, last_u, last_v);
		decodeUV(curr_rgba, curr_u, curr_v);
		
		// UV -> texel (usar floor y min para no pasarse con u/v == 1.0)
		int tex_w = image.GetWidth();
		int tex_h = image.GetHeight();
		
		int last_tex_x = std::min(tex_w - 1, (int)std::floor(last_u * tex_w));
		int last_tex_y = std::min(tex_h - 1, (int)std::floor(last_v * tex_h));
		int curr_tex_x = std::min(tex_w - 1, (int)std::floor(curr_u * tex_w));
		int curr_tex_y = std::min(tex_h - 1, (int)std::floor(curr_v * tex_h));
		
		// Pintar el segmento (ancho = 2*radius)
		drawLine(last_tex_x, last_tex_y, curr_tex_x, curr_tex_y, radius * 2.0f, color);
		texture.update(image);
	}
	
	last_x = xpos;
	last_y = ypos;
}


// ===== Funciones auxiliares para rasterizaci?n =====

glm::vec2 screenToTextureCoords(double x, double y, GLFWwindow *window)
{
	BufferSize bs = getBufferSize(window);
	// Convertir coordenadas de pantalla a coordenadas de textura
	// La ventana auxiliar muestra la textura completa, as? que es una conversi?n directa
	/*	std::cout<<bs.width<<std::endl;
	 */
	float tex_x = (float)x / bs.width;
	float tex_y = 1.0f - (float)y / bs.height; // Invertir Y:
	//	std::cout<<"text_x: "<<tex_x<<std::endl;
	//	std::cout<<"text_y: "<<tex_y<<std::endl;
	// Esto es porque:
	// En la ventana el 0,0 esta en la esquina superior izq, e Y crece hacia abajo

	// Convertir a coordenadas de p?xeles en la imagen
	int pixel_x = (int)(tex_x * image.GetWidth());
	int pixel_y = (int)(tex_y * image.GetHeight());

	//	std::cout<<"X: "<<pixel_x<<std::endl;
	//	std::cout<<"Y: "<<pixel_y<<std::endl;

	return glm::vec2(pixel_x, pixel_y);
}

// Dibuja un c?rculo de color sobre la imagen, centrado en (center_x, center_y) y con radio radius.
void drawPoint(int center_x, int center_y, float radius, const glm::vec4 &color)
{
	// Armar un cuadrado de radio centrado en el punto (para definir los limites)

	int min_x = std::max(0, (int)(center_x - radius));
	int max_x = std::min(image.GetWidth() - 1, (int)(center_x + radius));
	int min_y = std::max(0, (int)(center_y - radius));
	int max_y = std::min(image.GetHeight() - 1, (int)(center_y + radius));

	//	std::cout<<"min_X: "<<min_x<<std::endl;
	//	std::cout<<"max_X: "<<max_x<<std::endl;
	//	std::cout<<"min_Y: "<<min_y<<std::endl;
	//	std::cout<<"max_Y: "<<max_y<<std::endl;

	float radius_sq = radius * radius;

	// Por cada pixel:
	for (int y = min_y; y <= max_y; y++)
	{
		for (int x = min_x; x <= max_x; x++)
		{
			float dx = x - center_x;
			float dy = y - center_y;
			float dist_sq = dx * dx + dy * dy;

			// Solo lo que estan dentro del radio del circulo
			if (dist_sq <= radius_sq)
			{
				// SETRGB (FILA,COLUMNA, (COLOR))
				glm::vec4 existing_color = image.GetRGBA(y, x);
				float alpha = glm::clamp(color.a/radius, 0.0f, 1.0f); // usar alpha en [0,1]
				glm::vec4 blended_color = glm::mix(existing_color, color, alpha);
				image.SetRGBA(y, x, blended_color);
			}
		}
	}
}

void drawLine(int x0, int y0, int x1, int y1, float width, const glm::vec4 &color)
{
	int dx = x1 - x0;
	int dy = y1 - y0;

	// Caso: |dx| > |dy| ? recorrer en X
	if (std::abs(dx) > std::abs(dy))
	{
		// Asegurarse que x0 <= x1 (si no, swap)
		if (dx < 0)
		{
			std::swap(x0, x1);
			std::swap(y0, y1);
			dx = x1 - x0;
			dy = y1 - y0;
		}

		float m = (float)dy / (float)dx; // pendiente
		float y = (float)y0;

		for (int x = x0; x <= x1; x++)
		{
			drawPoint(x, (int)std::round(y), width / 2.0f, color);
			y += m;
		}
	}
	// Caso: |dy| >= |dx| ? recorrer en Y
	else
	{
		// Asegurarse que y0 <= y1 (si no, swap)
		if (dy < 0)
		{
			std::swap(x0, x1);
			std::swap(y0, y1);
			dx = x1 - x0;
			dy = y1 - y0;
		}

		float m = (float)dx / (float)dy; // pendiente inversa
		float x = (float)x0;

		for (int y = y0; y <= y1; y++)
		{
			drawPoint((int)std::round(x), y, width / 2.0f, color);
			x += m;
		}
	}
}
