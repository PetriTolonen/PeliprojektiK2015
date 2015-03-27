#include "Ammo.h"

Ammo::Ammo(std::string n, float s, int d, int p) :Object()
{
	texture_name = n +".png";
	set_texture(texture_name);
	object_texture.setSmooth(true);

	velocity = s;
	damage = d;
	penetration = p;

}

Ammo::Ammo() :Object()
{
	texture_name = "Ammo.png";
	set_texture(texture_name);
	object_texture.setSmooth(true);

	velocity = 2.0;
	damage = 15;
	penetration = 35;
}

void on_update(sf::Event event, sf::RenderWindow* win)
{

}


void Ammo::on_update(sf::Event event, sf::RenderWindow* win)
{

}

int Ammo::get_damage()
{
	return damage;
}

int Ammo::get_penetration()
{
	return penetration;
}

void Ammo::set_position(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Ammo::on_draw(sf::RenderWindow* win)
{
	win->draw(sprite_name);
}

