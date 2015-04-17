#include "ObjectManager.h"


ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager(void)
{
	std::for_each(objects.begin(), objects.end(), [](Object* e)
	{
		delete e;
		e = nullptr;
	});
}

void ObjectManager::free_objects() {
	std::for_each(destroyed_objects.begin(), destroyed_objects.end(), [this](Object* e) {
		objects.remove(e);

		delete e;
		e = nullptr;
	});

	destroyed_objects.clear();
}

void ObjectManager::free_ammos() {
	std::for_each(destroyed_ammos.begin(), destroyed_ammos.end(), [this](Object* e) {
		ammos.remove(e);

		delete e;
		e = nullptr;
	});

	destroyed_ammos.clear();
}

void ObjectManager::add_object(Object* const object) {
	assert(object != nullptr && !object->is_destroyed());

	bool add = !contains_object(object);

	if (add) 
	{
		objects.push_back(object);
	}
}

void ObjectManager::add_ammo(Object* const object) {
	assert(object != nullptr && !object->is_destroyed());

	bool add = !contains_object(object);

	if (add)
	{
		ammos.push_back(object);
	}
}

bool ObjectManager::contains_object(const Object* const entity) const 
{
	return std::find(objects.begin(), objects.end(), entity) != objects.end();
}

void ObjectManager::update(sf::Event event, sf::RenderWindow* win, Player* player)
{
	free_objects();
	free_ammos();

	std::for_each(objects.begin(), objects.end(), [this, &win, &event](Object* e)
	{
		if (e->is_destroyed())
		{
			destroyed_objects.push_back(e);
			return;
		}
		e->update(event, win);
	}); 


	std::for_each(ammos.begin(), ammos.end(), [this, &win, &event, &player](Object* e)
	{
		

		//float x = 0;
		//x = e->get_position().x;
		//std::cout << "Ammus x: "<< x << std::endl;

		//float x2 = 0;
		//x2 = player->get_position().x;
		//std::cout << "Pelaaja x: " << x2  << std::endl;

		

		//if (e->get_position().x < player->get_position().x - 500 && e->get_position().x > player->get_position().x + 500)
		//{
			std::cout << "Ammus tuhottu!" << std::endl;
			destroyed_ammos.push_back(e);
			return;
		//}
		e->update(event, win);
	});
}

void ObjectManager::draw(sf::RenderWindow* win)
{


	std::for_each(objects.begin(), objects.end(), [&win](Object* e)
	{
		e->draw(win);

	}
	);
}