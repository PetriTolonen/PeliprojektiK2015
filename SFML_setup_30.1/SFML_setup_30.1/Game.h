#ifndef GAME_H
#define GAME_H

#include "IncludeHelper.h"
#include "TileMap.h"
#include "ObjectManager.h"
#include "Object.h"
#include "Player.h"
//#include "Tank_hull.h"
#include "SplashScreen.h"
#include "MainMenu.h"

class Game
{
public:
	void run();
	void update();
	void gameloop(sf::RenderWindow *window, sf::View *view);
	void level_creation();
	void set_view(sf::View *view, Player *player);

private:
	static const int screen_widht = 1920;
	static const int screen_height = 1080;
	int level[1024];
	int level_trees[256];
	TileMap map;
	TileMap map2;

	int begin_of_game;

	static bool is_exiting();
	static void show_splash_screen(sf::RenderWindow *window);
	static void show_menu(sf::RenderWindow *window);

	enum game_state {
		uninitialized,
		showing_splash,
		paused,
		showing_menu,
		playing,exiting
	};
	static game_state _game_state;
};
#endif