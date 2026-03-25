.h = define la clase, solo se ponen los prototipos, sin codigo.
.cpp = se implementa el codigo y se detalla que hace cada metodo
	
///SFML 
///Inicializacion
*Lo habitual en SFML es tener una sola ventana (RenderWindow) y que todo ocurra ahi adentro
	
VideoMode vm(640,480); //Es un struct que declara la configuracion de la ventana
RenderWindow win(vm, "Juego"); //RenderWindow es una clase que representa una ventana, se le pasa un struct "VideoMode"

//Una vez que tenemos la ventana, pintamos el fondo
Color Color_Fondo (255,255,255,255); //Rojo Verde Azul Opacidad

//Cargar Imagen
Texture tex; //Texture es una clase que carga la imagen que esta en un archivo (jpg,png...)
if (!tex.loadFromFile ("imagen.png"))
	cerr<<"No se pudo cargar"<< endl;

//Ahora le cargamos la imagen en un Sprite 
Sprite spr;
spr.setTexture(tex); //Le decimos al Spirte que imagen queremos mostrar
spr.setPosition (100,100); //Le decimos al Sprite donde queremos mostrar la imagen
spr.setScale (1.0,2.0);
spr.setRotation (-45);
spr.setColor (Color (255,255,255,128));

	El sprite maneja el detalle de como y donde se va a mostrar la imagen
	Hay que cargar una sola vez cada textura, y luego la vas invocando mediante el sprite, ya que el Texture es muy caro y lento

///Loop de eventos
while (win.isOpen()) {
	//procesar eventos
	Event evt;
	while (win.pollEvent(evt)){ //pollEvent es un metodo de RenderWindow que va dando los eventos pendientes en orden de llegada
		if (evt.type==Event::Closed) //Pregunta de que tipo es el evento
			win.close();
	}
	//actualizar
	spr.move(1,1); //El sprite se va moviendo por la pantalla 
	
	//redibujar todo 
	win.clear(color_fondo); //borro todo el fondo
	win.draw(spr); //dibujo la imagen de nuevo
	win.display(); //muestro el nuevo fondo
}
  Por lo general para hacer juegos no se usa este mecanismo, se usa otro que veremos mas adelante, pero igual este while
  tiene que estar siempre, ya que sino se llena la lista de eventos y puede dejar de funcionar la Biblioteca, por mas que no usemos
  este mecanismo, tiene que estar. 

//Fijar velocidad de refresco
win.setFramerateLimit(60);
while (...) {
	...
}
//Velocidad variable
Clock clk;  //La velocidad avanza a la velocidad que pueda, se usa mas en juegos 3D para los casos en los que la placa de video es mala
while (...) {
	...
	float dt= clk.restart().asSeconds();
}

///DETECCION DE EVENTOS EN TIEMPO REAL 
void Tanque::actualizar(){
	if (Keyboard::isKeyPressed(Keyboard::Right))
		s.rotate(2);
	if (Keyboard::isKeyPressed(Keyboard::Left))
		s.rotate(-2);
	if (Keyboard::isKeyPressed(Keyboard::Up)){
		float ang= s.getRotation()*M_PI/180;
		s.move(cos(ang),sin(ang));
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)){
		float ang= s.getRotation()*M_PI/180;
		s.move(-cos(ang),-sin(ang));
	}
}
///No definas el setposition con numeros fijos, mejor dales un int x, int y Asi el main puede ir pasandole distintos lugares
///para que spawneen las naves, entonces podes hacer que cambien de lugar cada vez que pasen de nivel. Y es mejor todavia
///si la informacion sale de un archivo de texto, asi si queres cambiar algo de algun nivel, solo cambias unas lineas en el archivo
///y nada de codigo

///DETECCION DE INTERSECCIONES
FloatRect r1= sprite_1.getGlobalBounds(); //getGlobalBounds consigue un cuadrado que cubre a todo el sprite
FloatRect r2= sprite_2.getGlobalBounds(); //es bastsante burdo
if (r1.intersects(r2)){ cout<<"boooom"}

///OTRA FORMA MEJOR
bool colisiona(Disparo &d, Tanque &t) {
	Vector2f pd= d.verPos();
	Vector2f pt= t.verPos();
	Vector 2f v= pd-pt;
	if (sqrt(v.x*v.x+v.y*v.y)<30;
}
//Si ese vector mide menos que el radio del circulo es porque estoy adentro del circulo

///TEXTOS
m_font.loadFromFile("asap.ttf");

m_text.setFont(m_font);
m_text.setPosition(200,200);
m_text.setCharacterSize(40);
if (player1)
	m_text.setString("Player 1 wins");
else 
	m_text.setString("Player 2 wins");

//y despues dibujarlo
win.clear({0,0,0});
win.draw(m_text);


///CLASES SFML




































































































  

	













