#include "Tank_hull.h"

Tank_hull::Tank_hull(std::string tank_name)
{
	texture_name = tank_name + "_256.png";
	set_texture(texture_name);
}

Tank_hull::~Tank_hull(void)
{
}

void Tank_hull::on_update()
{

}

void Tank_hull::on_draw(sf::RenderWindow* win)
{
	win->draw(sprite_name);
}