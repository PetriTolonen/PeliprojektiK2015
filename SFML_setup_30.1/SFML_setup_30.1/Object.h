#ifndef OBJECT_H
#define OBJECT_H

#include "IncludeHelper.h"

class Object
{
public:
	Object();
	~Object();

	void set_texture(std::string texture_name);
	sf::Vector2f get_position();
	float get_rotation();
	void set_position(sf::Vector2f vector);
	float set_rotation();
private:
	sf::Vector2f position;
	float rotation;
	sf::Sprite sprite_name;
	sf::Texture object_texture;
};
#endif
