#ifndef PLAYER_H
#define PLAYER_H

#include "Tank.h"
#include "IncludeHelper.h"
#include "Object.h"
#include "Ammo.h"


class Player : public Object
{
public:
	Player(Tank_hull* t, Tank_turret* tt, float msf, float msb, float maf, float mab, float mmsf, float mmsb, float m);
	~Player(void);

	void on_update(sf::Event event, sf::RenderWindow* win);
	void update(sf::Event event, sf::RenderWindow* win);
	
	void reduce_health(int amount);
	void increase_health(int amount);
	void set_health();

	
	sf::Vector2f get_position();
	void on_draw(sf::RenderWindow* win);
	float get_position_x();
	float get_position_y();
	void set_position(float x, float y);
	float rotate(float rotation_speed);
	void set_rotation(float rot);
	void set_weight(float weight_hull); // + float weight_turret); sitten kun turret implementoidaan
	bool get_can_fire();


	sf::Vector2f get_distance_traveled() { return distance_traveled; }
private:
	
	int health;
	//sf::Sprite player_sprite_hull;
	Tank_turret* tt;
	Tank_hull* t;
	float x;
	float y;
	float turret_rotation_speed; //= 0;
	float hull_rotation_speed; //= 0;
	//----------Clock-----------------//
	sf::Time t1 = sf::seconds(0.1f);
	float _elapsed = t1.asSeconds();
	//-----------Main Gun---------------------//
	bool can_fire = true;

	//---------Tank_hull_statistics------//
	Tank_hull tank_hull;
	float M_PI = 3.14159265358979323846;
	float angle = 60 * M_PI / 2;
	float momentary_speed_forward = 0;
	float momentary_speed_backward = 0;
	float momentary_acceleration_forward = 0;
	float momentary_acceleration_backward = 0;
	float momentary_max_speed_forward = 0;
	float momentary_max_speed_backward = 0;
	float momentum = 0;
	float weight = 0;

	//------------------------------------//
	bool is_moving_forward = false;
	bool is_moving_backward = false;

	bool forward_is_pressed = false;
	bool backward_is_pressed = false;
	//std::string tank_name;

	/*
	float momentary_acceleration_forward = tank_hull.get_acceleration_forward();
	float momentary_max_speed_forward = tank_hull.get_max_speed_forward();
	*/

	sf::Vector2f distance_traveled;
};




#endif;