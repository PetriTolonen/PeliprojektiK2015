#ifndef PLAYER_H
#define PLAYER_H

#include "Tank.h"
#include "IncludeHelper.h"

class Player
{
public:
	Player();
	~Player(void);
	void update(float elapsed_time);
	void reduce_health(int amount);
	void increase_health(int amount);
	void set_health();


private:
	int health;
	



};




#endif;