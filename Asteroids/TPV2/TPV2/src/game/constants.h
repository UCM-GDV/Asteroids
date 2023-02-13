#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <SDL.h>
#include <iostream>
#include "../utils/Vector2D.h"
using namespace std;
using uint = unsigned int;

// WINDOW
const string GAME_NAME = "Asteroids";
const uint WIN_WIDTH = 1000;
const uint WIN_HEIGHT = 1000;
const SDL_Rect FULLWINDOW = { 0, 0, WIN_WIDTH, WIN_HEIGHT };

// FRAME TIMES
const double FRAME_TIME = 30;
const int DELAY_TIME = 17;

// TEXTURES
const string TEXTURES_FILE = "resources/config/textures.txt";
const int NUM_TEXTURES = 19;
const int BLOCK_NUMB = 3;
const int DIGITS_NUMB = 4;

// FIGHTER
const float FIGHTER_WIDTH = 50;
const float FIGHTER_HEIGHT = 50;
const Vector2D FIGHTER_VELOCITY = Vector2D(0, 0);
const float FIGHTER_ROTATION = 0;

// ASTEROID
const float ASTEROID_WIDTH_1 = 50;
const float ASTEROID_HEIGHT_1 = 50;
const float ASTEROID_WIDTH_2 = 25;
const float ASTEROID_HEIGHT_2 = 25;
const float ASTEROID_WIDTH_3 = 12;
const float ASTEROID_HEIGHT_3 = 12;
#endif