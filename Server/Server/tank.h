#ifndef _TANK_H_
#define _TANK_H_

#include "object.h"
#include "bullet.h"

class Tank : public Object
{
private:
	int		ID;
	int		HP;
	int		reload;

public:
	Tank(int id, int x, int y);
	int getID();
	int setHP();
	Bullet shoot()
	{
		Bullet b(posX + 10, posY + 10, dir);
		b.move(+1);
		return b;
	}
};

#endif