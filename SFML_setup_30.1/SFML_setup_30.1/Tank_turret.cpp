#include "Tank_turret.h"


Tank_turret::Tank_turret(std::string tank_turret_name, int af, int al, int ari, int are, float rot, int am, float acc, float aimt, float ts, int cd) : Object()
{

	texture_name = tank_turret_name + "_256.png";
	set_texture(texture_name);
	object_texture.setSmooth(true);
	//name = n;
	armor_front = af;
	armor_left = al;
	armor_rear = ari;
	armor_right = are;
	rotation_speed = rot;
	ammo_count = am;
	accuracy = acc;
	aim_time = aimt;
	traverse_speed = ts;
	cooldown = cd;

}

Tank_turret::Tank_turret() : Object()
{
	texture_name = "tank_tower_256.png";
	//name = "panzer part";
	set_texture(texture_name);
	armor_front = 15;
	armor_left = 15;
	armor_rear = 15;
	armor_right = 15;
	rotation_speed = 1;
	ammo_count = 100;
	accuracy = 0.35;
	aim_time = 1.7; 
	cooldown = 2;
}

Tank_turret::~Tank_turret(void)
{


}


void Tank_turret::rotate(float angle)
{



}

void Tank_turret::on_draw(sf::RenderWindow* win)
{
	win->draw(sprite_name);//hull_sprite_name);
}

void Tank_turret::on_update()
{

}

float Tank_turret::get_traverse_speed()
{
	return traverse_speed;
}

int Tank_turret::get_cooldown()
{
	return cooldown;
}