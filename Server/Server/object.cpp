#include "object.h"

void Object::move(int opt)
{
	posX += opt * dx[dir - 1] * vel;
	posY += opt * dy[dir - 1] * vel;
}

objectType Object::getType()
{
	return type;
}

int Object::getPosX()
{
	return posX;
}

int Object::getPosY()
{
	return posY;
}

int Object::getWidth()
{
	return width;
}

int Object::getHeight()
{
	return height;
}

int Object::getDir()
{
	return dir;
}