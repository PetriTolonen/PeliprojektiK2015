#ifndef TANK_TURRET_H
#define TANK_TURRET_H

#include "Tank_part.h"
#include "Object.h"

class Tank_turret : public Object
{
public:

	Tank_turret();
	Tank_turret(std::string tank_turret_name, int af,
		int al, int ari, int are, float rot, int am, float acc, float aimt);
	~Tank_turret(void);

	void rotate(float angle);
	void on_draw(sf::RenderWindow* win);
	void on_update();

protected:

	std::string texture_name;
	std::string tank_turret_name;
	int armor_front;
	int armor_left;
	int armor_right;
	int armor_rear;
	float rotation_speed;
	int ammo_count;
	float accuracy;
	float aim_time;




};
#endif;