#ifndef AMMO_H
#define AMMO_H

#include "IncludeHelper.h"
#include "Object.h"
#include <iostream>
#include "Box2D\Box2D.h"

class Ammo : public Object
{
public:

	Ammo(std::string n, float velo, int dmg, int pen, float x, float y, float scale, b2World world);
	Ammo();
	~Ammo();

	void on_update(sf::Event event, sf::RenderWindow* win);
	void update(sf::Event event, sf::RenderWindow* win);

	int get_damage();
	int get_penetration();

	sf::Vector2f get_position();

	void on_draw(sf::RenderWindow* win);

	float get_position(float x, float y);
	void set_position(float x, float y);
	float get_velocity();

	void start_contact();
	void end_contact();
	b2Body get_body();

protected:
	std::string texture_name;
	float velocity;
	int damage;
	int penetration;
	float x;
	float y;
	float radians;
	bool is_hit = false;
	b2Body* body;

	
};
#endif