#include "Object.h"


Object::Object()
{
}


Object::~Object()
{
}

void Object::set_texture(std::string texture_name)
{
	object_texture.loadFromFile(texture_name);
	sprite_name.setTexture(object_texture);
	sprite_name.setOrigin(object_texture.getSize().x / 2, object_texture.getSize().y / 2);
}

sf::Vector2f Object::get_position()
{
	sf::Vector2f location;
	location = sprite_name.getPosition();
	return location;
}

float Object::get_rotation()
{	
	float rotation;
	rotation = sprite_name.getRotation();
	return rotation;
}

void Object::set_position(sf::Vector2f vector)
{
	sprite_name.setPosition(vector);
}