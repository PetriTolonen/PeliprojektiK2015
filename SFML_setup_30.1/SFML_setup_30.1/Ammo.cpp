#include "Ammo.h"

Ammo::Ammo(std::string n, float s, int d, int p) :Object()
{
	texture_name = n +".png";
	set_texture(texture_name);
	object_texture.setSmooth(true);

	speed = s;
	damage = d;
	penetration = p;

}

Ammo::Ammo() :Object()
{
	texture_name = "Ammo.png";
	speed = 2.0;
	damage = 15;
	penetration = 35;
}