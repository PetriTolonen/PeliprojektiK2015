#ifndef TANK_HULL_H
#define TANK_HULL_H

#include "Tank_part.h"
#include "Object.h"

class Tank_hull :
	public Object
{
public:

	Tank_hull(std::string tank_name, float acf, float acb, float trs, float msf, float msb);
	Tank_hull();
	~Tank_hull(void);

	float get_acceleration_forward();
	float get_acceleration_backward();
	float get_traverse_speed();
	float get_max_speed_forward();
	float get_max_speed_backward();

protected:
	std::string texture_name;
	std::string tank_name;
	float acceleration_backward;
	float acceleration_forward;
	float traverse_speed;
	float max_speed_forward;
	float max_speed_backward;

	void on_update();
	void on_draw(sf::RenderWindow* win);
};
#endif