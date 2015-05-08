#include "AiManager.h"

AiManager::AiManager()
{

}

AiManager::~AiManager(void)
{

}

sf::Vector2f AiManager::get_player_position(Player* player)
{
	return player->get_position();
}

void AiManager::move_to(sf::Vector2f player_position, Enemy* enemy)
{
	
}

void AiManager::update(Player* player, Enemy* enemy)
{
	sf::Vector2f player_position_temp;
	player_position_temp = player->get_position();
	float player_rotation_temp = player->get_rotation();
	enemy->move_to(player_position_temp, player_rotation_temp);


	

}