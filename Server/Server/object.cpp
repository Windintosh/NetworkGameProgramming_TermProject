#include "object.h"
#include "main.cpp"

void Object::move(int opt)
{
	posX += opt * dx[dir - 1] * vel;
	posY += opt * dy[dir - 1] * vel;

    //If the dot collided or went too far to the left or right
    if ((posX < 0) || (posX + width > SCREEN_WIDTH) || checkCollision(mCollider, TANK))
    {
        //Move back
        posX -= opt * dx[dir - 1] * vel;
        mCollider.x = posX;
    }

    //If the dot collided or went too far up or down
    if ((posY < 0) || (posY + height > SCREEN_HEIGHT) || checkCollision(mCollider, wall))
    {
        //Move back
        posY -= opt * dy[dir - 1] * vel;
        mCollider.y = posY;
    }
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