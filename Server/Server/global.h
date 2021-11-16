#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include <string>

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;

// object
enum objectType { BULLET = 2, TANK = 4 };
const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { -1, 1, 0, 0 };

// tank
const int TANK_SIZE = 40;
const int TANK_VELOCITY = 1;
const int reloadTime = 2;
const int respawnTime = 4;

const int BULLET_SIZE = 4;
const int BULLET_VELOCITY = 2;

#endif