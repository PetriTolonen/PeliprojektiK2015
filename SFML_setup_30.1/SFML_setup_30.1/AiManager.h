#ifndef AIMANAGER_H
#define AIMANAGER_H

#include "Player.h"
#include "Enemy.h"


class AiManager
{
public:
	AiManager();
	~AiManager(void);
	float get_player_position(Player* player);

	void update();

private:


};
#endif;