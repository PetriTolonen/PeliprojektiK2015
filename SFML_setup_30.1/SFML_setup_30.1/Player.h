#ifndef PLAYER_H
#define PLAYER_H

#include "Tank.h"
#include "IncludeHelper.h"

class Player
{
public:
	Player(Tank_hull t);
	~Player(void);
	void update();
	void reduce_health(int amount);
	void increase_health(int amount);
	void set_health();
	void set_position(float x, float y);
	sf::Vector2f get_position();
	void on_draw(sf::RenderWindow* win);
	

private:
	int health;
	//sf::Sprite player_sprite_hull;
	Tank_hull t;
//	float x;
//	float y;



};




#endif;