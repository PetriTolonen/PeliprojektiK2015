#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "Object.h"
#include <list>
#include <cassert>
#include "Player.h"

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager(void);

	void add_object(Object* const object);
	void add_ammo(Object* const object);
	bool contains_object(const Object* const entity) const;
	void update(sf::Event event, sf::RenderWindow* win, Player* player);
	void draw(sf::RenderWindow* win);
private:
	std::list<Object* const> objects;
	std::vector<Object* const> find_results;
	std::list<Object* const> destroyed_objects;
	std::list<Object* const> ammos;
	std::list<Object* const> destroyed_ammos;
	

	void free_objects();
	void free_ammos();
};
#endif
