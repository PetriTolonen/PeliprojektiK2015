#ifndef GAME_H
#define GAME_H

#include "IncludeHelper.h"

class Game
{
public:
	void run();
	void update();
	void gameloop(sf::RenderWindow *window, sf::View *view);

private:
	static const int screen_widht = 1280;
	static const int screen_height = 720;

};
#endif
