#include "Ammo.h"

Ammo::Ammo(std::string n, float velo, int dmg, int pen, float x, float y, float scale, b2World world) :Object()
{
	std::cout << "luo ammuksen" << std::endl;
	texture_name = n +".png";
	set_texture(texture_name);
	object_texture.setSmooth(true);

	//--ammo_b2_body-----//
	
	b2BodyDef ammoBodyDef;
	ammoBodyDef.position = b2Vec2(x / scale, y / scale);
	ammoBodyDef.type = b2_kinematicBody;
	ammoBodyDef.bullet = true;

	body = world.CreateBody(&ammoBodyDef);

	b2PolygonShape shape_ammo;
	shape_ammo.SetAsBox((20.f) / scale, (20.f) / scale);
	b2FixtureDef AmmoFixtureDef;
	AmmoFixtureDef.density = 1.f;
	AmmoFixtureDef.friction = 0.7f;
	AmmoFixtureDef.shape = &shape_ammo;
	body->CreateFixture(&AmmoFixtureDef);

	body->SetUserData(this);
	//------------------------//

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

b2Body Ammo::get_body()
{
	return *body;
}

void Ammo::start_contact()
{
	is_hit = true;
}

void Ammo::end_contact()
{
	is_hit = false;
}