#include "Game.h"

void Game::run()
{
	//------Screen setup------//
	sf::Vector2i screen_dimensions(screen_widht, screen_height);
	sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(screen_dimensions.x, screen_dimensions.y), "Tank Hunter Arcade");	
	window->setFramerateLimit(60);

	//------View setup------//
	sf::View *view = new sf::View(sf::FloatRect(0, 0, screen_dimensions.x, screen_dimensions.y));
	//view.reset(sf::FloatRect(0, 0, screen_dimensions.x, screen_dimensions.y));
	view->setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

	gameloop(window, view);
}

//-----Game_loop-----//
void Game::gameloop(sf::RenderWindow *window, sf::View *view)
{
	while (window->isOpen())
	{
		sf::Clock clock;
		sf::Time elapsed = clock.getElapsedTime();


		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					window->close();
					break;
				}

			}

		}
		window->clear(sf::Color(100,200,0));
		window->setView(*view);
		//window.draw(map);
		//window.draw(sprite_tank_hull);
		//window.draw(sprite_tank_turret);
		//window.draw(map2);
		window->display();
	}

}