#ifndef OBJETO_H
#define OBJETO_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
using namespace sf;

class Objeto {
public:
	Objeto(std::string fname);
	void Dibujar(RenderWindow &window);
	Vector2f verPosicion();
	bool CollideWith(const Objeto &o) const;
protected:
	Texture m_texture;
	Sprite m_sprite;
};

#endif


