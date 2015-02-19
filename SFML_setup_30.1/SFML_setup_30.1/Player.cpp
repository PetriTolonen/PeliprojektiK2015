#include "Player.h"

Player::Player()
{

}

Player::~Player(void)
{

}


void Player::update(float elapsed_time)
{
	//----------Clock-----------------//
	sf::Time t1 = sf::seconds(0.1f);
	float _elapsed = t1.asSeconds();


	//---------Tank_hull_statistics------//
	Tank_hull tank_hull;
	float M_PI = 3.14159265358979323846;
	float angle = 60 * M_PI / 2;
	float momentary_speed_forward = 0;
	float momentary_speed_backward = 0;
	float momentary_acceleration_forward = 0;
	float momentary_acceleration_backward = 0;
	float momentary_max_speed_forward = 0;

	momentary_acceleration_forward = tank_hull.get_acceleration_forward();
	momentary_max_speed_forward = tank_hull.get_max_speed_forward();

	//----------------Key_Pressing_check--------------------------------------//
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		

		

		momentary_speed_forward += _elapsed * momentary_acceleration_forward;

		if (momentary_speed_forward > momentary_max_speed_forward)
		{
			momentary_speed_forward = momentary_max_speed_forward;
		}

		//tank_hull

		/*
		hull_movement_speed_forwards += _elapsed * hull_movement_acceleration;


		if (hull_movement_speed_forwards > hull_movement_speed_forwards_max)
		{
		hull_movement_speed_forwards = hull_movement_speed_forwards_max;
		}


		//Tank hull moves now to the direction it faces.
		sprite_tank_hull.move(sin(sprite_tank_hull.getRotation()*3.14159265 / 180) * hull_movement_speed_forwards, cos(sprite_tank_hull.getRotation()*3.14159265 / 180)*-hull_movement_speed_forwards);
		sprite_tank_turret.setPosition(sprite_tank_hull.getPosition());
		view.setCenter(sprite_tank_hull.getPosition());

		//	//----------------Tank_rotation_and_movement-----------------------------------------------------//
		//	float rot_turret = 0;
		//	float rot_hull = 0;
		//	float turret_rot_speed = 1.2;
		//	float hull_rot_speed = 0.8;
		//
		//	float o_clock = 1 / 60;
		//
		//	float hull_movement_acceleration = 0.2;
		//	float hull_movement_speed_forwards = 0;
		//	float hull_movement_speed_forwards_max = 2.1;
		//
		//	float hull_movement_speed_backwards = 0;
		//	float hull_movement_speed_backwards_max = 0.7;
		//
		//	float speed = 5;
		//	float angle = 60 * M_PI / 2;
		//
		//	float move_x = speed * cos(angle);
		//	float move_y = speed * sin(angle);
		//
		//
		//
		//	//-----------------------------------------------------------------------------------------------//
		//

		*/
					

	}



}