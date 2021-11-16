#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "global.h"

class Object
{
protected:
	objectType	type;
	int			posX, posY;
	int			width, height;
	int			vel, dir;

public:
	Object(objectType t, int x, int y, int w, int h, int v, int d):
		type(t), posX(x), posY(y), width(w), height(h), vel(v), dir(d) {}
	void move(int opt);
	objectType getType();
	int getPosX();
	int getPosY();
	int getWidth();
	int getHeight();
	int getDir();
};

#endif