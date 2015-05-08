#ifndef AIMANAGER_H
#define AIMANAGER_H

#include "Player.h"
#include "Enemy.h"


class AiManager
{
public:
	AiManager();
	~AiManager(void);
	sf::Vector2f get_player_position(Player* player);

	void update();

private:
	bool at_destination;

};
#endif;