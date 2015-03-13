#include "ObjectManager.h"


ObjectManager::ObjectManager()
{
}

void ObjectManager::free_objects() {
	std::for_each(destroyed_objects.begin(), destroyed_objects.end(), [this](Object* e) {
		objects.remove(e);

		delete e;
		e = nullptr;
	});

	destroyed_objects.clear();
}

void ObjectManager::add_object(Object* const object) {
	assert(object != nullptr && !object->is_destroyed());

	bool add = !contains_object(object);

	if (add) {
		objects.push_back(object);
	}
}

bool ObjectManager::contains_object(const Object* const entity) const 
{
	return std::find(objects.begin(), objects.end(), entity) != objects.end();
}

void ObjectManager::update()
{
	free_objects();

	std::for_each(objects.begin(), objects.end(), [this](Object* e)
	{
		if (e->is_destroyed())
		{
			destroyed_objects.push_back(e);
			return;
		}
		e->update();
	});
}

void ObjectManager::draw()
{
	std::for_each(objects.begin(), objects.end(), [](Object* e)
	{
		delete e;
		e = nullptr;
	});
}