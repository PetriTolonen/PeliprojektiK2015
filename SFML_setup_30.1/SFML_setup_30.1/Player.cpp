#include "Player.h"

Player::Player(Tank_hull* t, Tank_turret* tt, float msf, float msb, float maf, float mab, float mmsf, float mmsb, float m) : Object()
{
	this->t = t;
	this->tt = tt;
	turret_rotation_speed = tt->get_traverse_speed();
	hull_rotation_speed = t->get_traverse_speed();
	

	momentary_speed_forward = msf;
	momentary_max_speed_backward = msb;
	momentary_acceleration_forward = maf;
	momentary_acceleration_backward = mab;
	momentary_max_speed_forward = mmsf;
	momentary_max_speed_backward = mmsb;
	momentum = m;
}

Player::~Player(void)
{

}

void Player::update(sf::Event event, sf::RenderWindow* win)
{

}

void Player::on_update(sf::Event event, sf::RenderWindow* win)
{

	////----turret_to_mouse----//

	sf::Vector2i pixel_pos = sf::Mouse::getPosition(*win);
	sf::Vector2f coord_pos = win->mapPixelToCoords(pixel_pos);

	float dx = x - coord_pos.x;
	float dy = y - coord_pos.y;
	float rotation = (atan2(dy, dx)) * 180 / M_PI;

	float rotation2 = (rotation + 180) - tt->get_rotation();

	if (rotation2 < 0)
	{
		rotation2 += 360;
	}
	
	//If tank turret close to mouse rotation set exactly to mouse rotation
	if (rotation2 < 180+0.6 && rotation2 > 180 - 0.6)
	{
		tt->get_sprite().setRotation(rotation);
	}
	else
	{
		if (rotation2 >180)
		{
			tt->get_sprite().rotate(tt->get_traverse_speed()* 10 * _elapsed);

		}
		if (rotation2 <180)
		{
			tt->get_sprite().rotate(-tt->get_traverse_speed()*10 * _elapsed);
	}
	
		
	}
	//std::cout << rotation + 180 << " " << tt->get_rotation() << std::endl;
	//std::cout << tt->get_rotation() <<"                  " << rotation +180<<  std::endl;
	
	//----------------Key_Pressing_check--------------------------------------//
	//Checks movement stuff
	
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{

		if (is_moving_backward == false)
		{
			momentary_acceleration_forward = tank_hull.get_acceleration_forward();
			momentary_max_speed_forward = tank_hull.get_max_speed_forward();
			momentary_speed_forward += _elapsed * momentary_acceleration_forward;



			if (momentary_speed_forward > momentary_max_speed_forward)
			{
				momentary_speed_forward = momentary_max_speed_forward;
			}

			set_position(x + (sin(t->get_rotation()*M_PI / 180)*-momentary_speed_forward), y + (cos(t->get_rotation()*M_PI / 180)*momentary_speed_forward));

			is_moving_forward = true;
		}

		if (is_moving_backward == true)
		{
			momentary_acceleration_forward = tank_hull.get_acceleration_forward();
			momentary_max_speed_forward = tank_hull.get_max_speed_forward();
			momentary_speed_forward += _elapsed * momentary_acceleration_forward;

			momentary_speed_backward -= momentary_speed_forward;
		}
		

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (is_moving_forward == false)
		{
			momentary_acceleration_backward = tank_hull.get_acceleration_backward();
			momentary_max_speed_backward = tank_hull.get_max_speed_backward();
			momentary_speed_backward += _elapsed * momentary_acceleration_backward;

			if (momentary_speed_backward > momentary_max_speed_backward)
			{
				momentary_speed_backward = momentary_max_speed_backward;
			}

			set_position(x + (sin(t->get_rotation()*M_PI / 180)*momentary_speed_backward), y + (cos(t->get_rotation()*M_PI / 180)*-momentary_speed_backward));

			is_moving_backward = true;

		}

		if (is_moving_forward == true)
		{

			momentary_acceleration_backward = tank_hull.get_acceleration_backward();
			momentary_max_speed_backward = tank_hull.get_max_speed_backward();
			momentary_speed_backward += _elapsed * momentary_acceleration_backward;


			momentary_speed_forward -= momentary_speed_backward;
		}



	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
			t->get_sprite().rotate(hull_rotation_speed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		t->get_sprite().rotate(-hull_rotation_speed);
	}
		

	//----------------------------------------------------Key realease events--------------------------------//
	//So the tank is required to accelerate everytime it stops
	
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::W)
		{
			momentary_speed_forward -= 0.10;
			if (momentary_speed_forward <= 0.05)
			{
				momentary_speed_forward = 0;
				is_moving_forward = false;
			}
				
		}
	}
	
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::S)
		{
			momentary_speed_backward -= 0.10;
			if (momentary_speed_backward <= 0.05)
			{
				momentary_speed_backward = 0;
				is_moving_backward = false;
			}
				
			
		}
	}


	//----------------------momentum to move tank forward after key is released------------------------------------//
	//to move tank even if key is released to make it feel more like a tank.

	 

	if (is_moving_forward == true) // && !event.KeyPressed)
	{
		set_position(x + (sin(t->get_rotation()*M_PI / 180)*-momentary_speed_forward), y + (cos(t->get_rotation()*M_PI / 180)*momentary_speed_forward));
	}
	
	if (is_moving_backward == true) // && !event.KeyPressed)
	{
		set_position(x + (sin(t->get_rotation()*M_PI / 180)*momentary_speed_backward), y + (cos(t->get_rotation()*M_PI / 180)*-momentary_speed_backward));
	}
	
	

	

//----------Distance travelled--------------------------//

	if (t->get_position().y > distance_traveled.y)
	{
		distance_traveled.y = t->get_position().y;
	}
	if (t->get_position().x > 0 + (1920 / 2) && t->get_position().x < 4096.f - (1920 / 2))
	{
		distance_traveled.x = t->get_position().x;
	}
	
	//debuggausta varten kirjoittaa consoleen pelaajan sijaintia.
	//std::cout << tt->get_position().x << " " << tt->get_position().y << std::endl;
}

void Player::set_position(float x, float y)
{
	this->x = x;
	this->y = y;

	t->set_position(this ->x, this->y);
	tt->set_position(this->x, this->y);
	
}

float Player::rotate(float rotation_speed)
{
	return 0;//t->set_rotation(rotation_speed);

}

sf::Vector2f Player::get_position()
{
	return	t->get_position();
}

void Player::on_draw(sf::RenderWindow* win)
{
	t->on_draw(win);
	tt->on_draw(win);
}

void Player::set_rotation(float rot)
{
	//rotation = rot;
}


/*
void Player::set_weight(float weight_turret) //, float weight_hull)
{
	weight = weight_turret + weight_hull;
}
*/


/*

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
					

	

	