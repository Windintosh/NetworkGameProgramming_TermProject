#ifndef _BULLET_H_
#define _BULLET_H_

#include "object.h"

class Bullet : public Object
{
public:
	Bullet(int x, int y, int d):
		Object(BULLET, x, y, BULLET_SIZE, BULLET_SIZE, BULLET_VELOCITY, d) {}
};

#endif