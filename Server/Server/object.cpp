#include "object.h"
#include "main.cpp"
#include "tank.h"

void Object::move(int opt) //logic
{
    switch (opt) {
        //posX += opt * dx[dir - 1] * vel;
        //posY += opt * dy[dir - 1] * vel;
    case 1:
        posX += dx[dir - 1] * vel;
        break;
    case 2:
        posX -= dx[dir - 1] * vel;
        break;
    case 3:
        posY += dy[dir - 1] * vel;
        break;
    case 4:
        posY -= dy[dir - 1] * vel;
        break;
    case 5:
        break;

    }
    //If the dot collided or went too far to the left or right
    if ((posX < 0) || (posX + width > SCREEN_WIDTH) || checkCollision(mCollider, Tank.mCollider)) //every object
    {
        //Move back
        posX -= opt * dx[dir - 1] * vel;
        mCollider.x = posX;
    }

    //If the dot collided or went too far up or down
    if ((posY < 0) || (posY + height > SCREEN_HEIGHT) || checkCollision(mCollider, Tank.mCollider))
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

void Object::setCollider()
{
    mCollider.w = width;
    mCollider.h = height;
}