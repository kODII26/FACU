///PROYECTO TIPS

Todos los .h terminan con #endif 
Todas las ventanas van creadas con punteros para que queden abiertas hasta el proximo evento (cerrar, aceptar)
		si la creas sin puntero, apenas se abre se cierra y no se alcanza a ver (con puntero queda viva
		ya que se pone el new pero no el delete, entonces zinjai no elimina el objeto automaticamente)

Para hacer que una ventana creada normalmente no se cierre insta, se usa el .ShowModal() esto tambien hace
	que la ventana base quede sin uso hasta que se cierre la ventana hija (Esto solo funciona con 
	Cuadro de Dialogo, no con una ventana normal)
	Si usas el Modal, podes tambien esperar a que te retorne algo (1 si se clickeo Aceptar, 0 si se clickeo
	Cancelar) entonces despues con un if preguntas si es 1, hay que refrescar la grilla para agregar la nueva
	persona
///PASOS
	Paso 1: Nada de GUIs
		Modelar el problema y armar una biblioteca de clases y funciones que modelen mi problema de forma independiente
		de la interfaz
	Paso 2: Nada de GUIs
		Probar el modelo, asegurarse de que las clases y funciones andan y tienen todo lo necesario
	Paso 3: Hacer la GUI

//Eventos
	Un evento es un sueceso interesanta para una aplicacion:
		Presionar una tecla
		Click sobre algun boton
		Cambio de tamaño la ventana
		Elegir alguna opcion del menu
		Cerrar la ventana
		
//Eventos y objetos
	Las ventanas son clases:
		Los controles son sus atributos
		Los eventos sus metodos
	Crear una ventana es instanciar una clase:
		Los controles se agregan por composicion

	
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		

