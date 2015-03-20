#include "SplashScreen.h"


void SplashScreen::show(sf::RenderWindow* win)
{
	sf::Texture image;
	if (image.loadFromFile("splash_screen.png") != true)
	{
		return;
	}

	sf::Sprite sprite(image);

	win->draw(sprite);
	win->display();

	sf::Event event;
	while (true)
	{
		while (win->pollEvent(event))
		{
			if (event.type == sf::Event::EventType::KeyPressed
				|| event.type == sf::Event::EventType::MouseButtonPressed
				|| event.type == sf::Event::EventType::Closed)
			{
				return;
			}
		}
	}
}
