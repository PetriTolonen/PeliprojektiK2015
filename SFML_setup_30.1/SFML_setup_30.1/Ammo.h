#ifndef AMMO_H
#define AMMO_H

#include "IncludeHelper.h"
#include "Object.h"
#include <iostream>

class Ammo : public Object
{
public:

	Ammo(std::string n,float s, int d, int p);
	Ammo();
	~Ammo(void);

	void on_update(sf::Event event, sf::RenderWindow* win);
	void update(sf::Event event, sf::RenderWindow* win);

	int get_damage();
	int get_penetration();

	sf::Vector2f get_position();

	void on_draw(sf::RenderWindow* win);

	float get_position(float x, float y);
	void set_position(float x, float y);

protected:
	std::string texture_name;
	float velocity;
	int damage;
	int penetration;
	float x;
	float y;
	bool is_hit = false;
	
};
#endif