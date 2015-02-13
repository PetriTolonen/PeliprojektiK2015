#ifndef TANK_HULL_H
#define TANK_HULL_H

#include "Tank_part.h"
#include "Object.h"

class Tank_hull :
	public Object
{
public:

	Tank_hull(std::string tank_name);
	~Tank_hull(void);


protected:
	std::string texture_name;
	std::string tank_name;
};
#endif