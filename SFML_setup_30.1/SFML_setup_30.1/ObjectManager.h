#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "Object.h"
#include <list>
#include <cassert>

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	void add_object(Object* const object);
	bool contains_object(const Object* const entity) const;
	void update();
	void draw();
private:
	std::list<Object* const> objects;
	std::vector<Object* const> find_results;
	std::list<Object* const> destroyed_objects;

	void free_objects();
};
#endif
