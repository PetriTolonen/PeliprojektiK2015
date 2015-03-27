#ifndef AMMO_H
#define AMMO_H


#include "Object.h"

class Ammo : public Object
{
public:

	Ammo(std::string n,float s, int d, int p);
	Ammo();
	
	~Ammo();

protected:
	std::string texture_name;
	float speed;
	int damage;
	int penetration;

};
#endif