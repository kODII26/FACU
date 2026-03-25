#ifndef OBJETO_H
#define OBJETO_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
using namespace sf;

class Objeto {
public:
	Objeto(int num);
	void Dibujar(RenderWindow &window);
	Vector2f verPosicion();
	bool CollideWith(const Objeto &o) const;
	Sprite verSprite(){return m_sprite;}
protected:
	Texture m_tex_player;
	Texture m_tex_enemy;
	Sprite m_sprite;
};

#endif


