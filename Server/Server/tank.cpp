#include "tank.h"

Tank::Tank(int id, int x, int y) :
	Object(TANK, x, y, TANK_SIZE, TANK_SIZE, TANK_VELOCITY, 2), ID(id), HP(3), reload(0) {}

int Tank::getID()
{
	return ID;
}

int Tank::setHP()
{
	return HP;
}