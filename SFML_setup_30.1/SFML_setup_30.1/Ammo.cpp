#include "Ammo.h"

Ammo::Ammo(std::string n, float velo, int dmg, int pen, float x, float y) :Object()
{
	std::cout << "luo ammuksen" << std::endl;
	texture_name = n +".png";
	set_texture(texture_name);
	object_texture.setSmooth(true);


	velocity = velo;
	damage = dmg;
	penetration = pen;
	

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

float Ammo::get_velocity()
{
	return velocity;
}

Ammo::~Ammo()
{

}

void Ammo::set_velocity(float x, float y, b2Body *ammo_body)
{
	ammo_body->SetLinearVelocity(b2Vec2(x, y));
}

void Ammo::start_contact()
{
	is_hit = true;
}

void Ammo::end_contact()
{
	is_hit = false;
}
void Ammo::set_coord(float _x, float _y)
{
	x = _x;
	y = _y;
}