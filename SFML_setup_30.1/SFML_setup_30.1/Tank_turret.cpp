#include "Tank_turret.h"


Tank_turret::Tank_turret(std::string tank_turret_name, int af, int al, int ari, int are, float rot, int am, float acc, float aimt) : Object()
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

}

Tank_turret::Tank_turret() : Object()
{
	//name = "panzer part";
	set_texture(texture_name);
	armor_front = 15;
	armor_left = 15;
	armor_rear = 15;
	armor_right = 15;
	rotation_speed = 1;

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