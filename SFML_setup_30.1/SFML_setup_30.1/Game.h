#ifndef GAME_H
#define GAME_H

#include "IncludeHelper.h"
#include "TileMap.h"
#include "ObjectManager.h"
#include "Object.h"
#include "Player.h"
#include "ObjectManager.h"
#include "Ammo.h"
#include "Enemy.h"
#include "AiManager.h"
#include "SplashScreen.h"
#include "MainMenu.h"

#include "Box2D\Box2D.h"
#include "ContactChecker.h"

class Game
{
public:
	void run();
	void update();
	void gameloop(sf::RenderWindow *window, sf::View *view, MainMenu *main_menu);
	void level_creation();
	void set_view(sf::View *view, Player *player);
	
	void fire_main_gun(b2World& world, int MouseX, int MouseY, Player *player, Ammo *ammo); //, Ammo *ammo);

	//void CreateBox(b2World& world, int MouseX, int MouseY);

private:
	static const int screen_widht = 1920;
	static const int screen_height = 1080;
	int level[1024];
	int level_trees[256];
	TileMap map;
	TileMap map2;

	static ObjectManager o_manager;

	int begin_of_game;

	static bool is_exiting();
	static void show_splash_screen(sf::RenderWindow *window);
	static void show_menu(sf::RenderWindow *window); //, MainMenu *main_menu);
	MainMenu main_menu;
	enum game_state {
		uninitialized,
		showing_splash,
		paused,
		showing_menu,
		playing,exiting
	};
	static game_state _game_state;
	Ammo ammo();
	std::vector<Ammo*> ammo_vector;

	//b2Fixture *ammo_fixture;
	//b2Fixture *box_fixture;

	MyContactListener *ContactListener;
};
#endif