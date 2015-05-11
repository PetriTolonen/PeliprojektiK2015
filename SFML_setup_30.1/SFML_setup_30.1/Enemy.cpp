#include "Enemy.h"


Enemy::Enemy(b2Body* enemy_body, Tank_hull* t, Tank_turret* tt, float msf, float msb, float maf, float mab, float mmsf, float mmsb, float m, int mcd) : Object()
{
	this->enemy_body = enemy_body;
	this->t_hull = t;
	this->t_turret = tt;

	turret_rotation_speed = tt->get_traverse_speed();
	hull_rotation_speed = t->get_traverse_speed();
	//enemy_body->SetUserData(this);

	momentary_speed_forward = msf;
	momentary_max_speed_backward = msb;
	momentary_acceleration_forward = maf;
	momentary_acceleration_backward = mab;
	momentary_max_speed_forward = mmsf;
	momentary_max_speed_backward = mmsb;
	momentum = m;
	momentary_cooldown = mcd;
	at_destination = true;

	//player position random offsets
	random_x = rand() % 150 + 75;
	random_y = rand() % 150 + 75;

	health = 20;
	animation_played = false;
}

Enemy::~Enemy(void)
{

}

void Enemy::on_update(sf::Event, sf::RenderWindow* win)
{
	
	set_position(enemy_body->GetPosition().x, enemy_body->GetPosition().y);

	t_hull->get_sprite().setRotation((enemy_body->GetAngle() * (180.0f / M_PI)));
}

void Enemy::update(sf::Event event, sf::RenderWindow* win)
{

}

void Enemy::on_draw(sf::RenderWindow* win)
{
	if (health > 0)
	{
		t_hull->get_sprite().setColor(sf::Color(200, 0, 0));
		t_turret->get_sprite().setColor(sf::Color(200, 0, 0));
	}
	if (health < 0)
	{
		t_hull->get_sprite().setColor(sf::Color(50, 0, 0));
		t_turret->get_sprite().setColor(sf::Color(50, 0, 0));
	}

	t_hull->on_draw(win);
	t_turret->on_draw(win);
}

void Enemy::reduce_health(int amount)
{
	health -= amount;

	if (health == 0)
	{

	}
}

void Enemy::set_position(float x, float y)
{
	this->x = x*30.0;
	this->y = y*30.0;

	t_hull->set_position(this->x, this->y);
	t_turret->set_position(this->x, this->y);
}

float Enemy::get_rotation()
{
	return enemy_body->GetAngle();
}

float Enemy::get_rotation_turret()
{
	return t_turret->get_sprite().getRotation();
}

int Enemy::get_cooldown()
{
	return momentary_cooldown;
}

sf::Vector2f Enemy::get_position()
{
	sf::Vector2f location(enemy_body->GetPosition().x*30.0, enemy_body->GetPosition().y*30.0);
	return location;
}

bool Enemy::get_can_fire()
{
	return can_fire;
}

void Enemy::set_cooldown()
{
	momentary_cooldown = t_turret->get_cooldown();
}

b2Body* Enemy::get_body()
{
	return enemy_body;
}

void Enemy::move_to(sf::Vector2f player_position, float player_rotation)
{
	//----------------------turret_rotation_towards_player--------------------------------//
	if (health>0)
	{
		sf::Vector2f coord_pos = player_position;

		float dx = x - coord_pos.x;
		float dy = y - coord_pos.y;
		float rotation = (atan2(dy, dx)) * 180 / M_PI;

		float rotation2 = (rotation + 180) - t_turret->get_rotation();

		if (rotation2 < 0)
		{
			rotation2 += 360;
		}

		//If tank turret close to mouse rotation set exactly to player rotation
		if (rotation2 < 180 + 0.6 && rotation2 > 180 - 0.6)
		{
			t_turret->get_sprite().setRotation(rotation);
		}
		else
		{
			if (rotation2 >180)
			{
				t_turret->get_sprite().rotate(t_turret->get_traverse_speed() * 10 * _elapsed);


			}
			if (rotation2 <180)
			{
				t_turret->get_sprite().rotate(-t_turret->get_traverse_speed() * 10 * _elapsed);

			}


		}
		//----------------------end_of_turret_rotation_towards_player--------------------------------//


		float dbx = x - coord_pos.x + random_x;
		float dby = y - coord_pos.y + random_y;

		float body_rotation = (atan2(dby, dbx)) * 180 / M_PI;

		float body_rotation2 = (body_rotation + 180) - enemy_body->GetAngle() * 180 / M_PI;

		while (body_rotation2 <= 0){
			body_rotation2 += 360;
		}
		while (body_rotation2 > 360){
			body_rotation2 -= 360;
		}

		//std::cout << body_rotation2 << "  " << body_rotation << std::endl;
		//if (body_rotation2 < 0)
		//{
		//	body_rotation2 += 360;
		//	
		//}
		//else

		if (body_rotation2 + 90 >180)
		{
			//t_turret->get_sprite().rotate(t_turret->get_traverse_speed() * 10 * _elapsed);
			enemy_body->SetAngularVelocity(hull_rotation_speed);

		}
		if (body_rotation2 + 90<180)
		{
			//t_turret->get_sprite().rotate(-t_turret->get_traverse_speed() * 10 * _elapsed);
			enemy_body->SetAngularVelocity(-hull_rotation_speed);
		}


		/*if (at_destination == false)
		{
		temp--;
		if (temp <= 0)
		{
		at_destination == true;
		temp = 1000;
		}
		}*/


		momentary_acceleration_forward = tank_hull.get_acceleration_forward();
		momentary_max_speed_forward = tank_hull.get_max_speed_forward();
		momentary_speed_forward += _elapsed * momentary_acceleration_forward;

		if (momentary_speed_forward > momentary_max_speed_forward)
		{
			momentary_speed_forward = momentary_max_speed_forward;
		}

		enemy_body->SetLinearVelocity(b2Vec2(b2Vec2(sin(enemy_body->GetAngle())*-momentary_speed_forward, cos(enemy_body->GetAngle())*momentary_speed_forward)));
	}
}

int Enemy::get_health()
{
	return health;
}

bool Enemy::get_has_died()
{
	return animation_played;
}

void Enemy::set_animation_has_played()
{
	animation_played = true;
}
//
////-------------------------------rotate-----------------------------------------------//
//float x_player = t_turret->get_position().x;
//float y_player = t_turret->get_position().y;
//
//float rotation = (atan2(y_player, x_player)) * 180 / M_PI;
//float rotation2 = (rotation + 180) - t_turret->get_rotation();
//
//if (rotation2 < 0)
//{
//	rotation2 += 360;
//}
//
//
//if (rotation2 < 180 + 0.6 && rotation2 > 180 - 0.6)
//{
//	t_turret->get_sprite().setRotation(rotation);
//}
//else
//{
//	if (rotation2 >180)
//	{
//		t_turret->get_sprite().rotate(t_turret->get_traverse_speed() * 10 * _elapsed);
//
//	}
//	if (rotation2 <180)
//	{
//		t_turret->get_sprite().rotate(-t_turret->get_traverse_speed() * 10 * _elapsed);
//	}
//
//
//}
////---------------------------end rotation------------------------------------------//