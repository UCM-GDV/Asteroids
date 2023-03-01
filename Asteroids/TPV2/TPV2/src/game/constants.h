#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <SDL.h>
#include <iostream>
#include "../utils/Vector2D.h"
using namespace std;

// WINDOW
const string GAME_NAME = "Asteroids";
const float WIN_WIDTH = 1000;
const float WIN_HEIGHT = 600;
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
const Vector2D SPEED_LIMIT = { 0, 3.0f };

// ASTEROID
const int ASTEROIDS_DELAY_TIME = 5;
const float ASTEROID_WIDTH_1 = 50;
const float ASTEROID_HEIGHT_1 = 50;
const float ASTEROID_WIDTH_2 = 25;
const float ASTEROID_HEIGHT_2 = 25;
const float ASTEROID_WIDTH_3 = 12;
const float ASTEROID_HEIGHT_3 = 12;
const int ASTEROID_WHITE_WIDTH = 85;
const int ASTEROID_WHITE_HEIGHT = 100;
const int ASTEROID_WHITE_NUMCOLS = 5;
const int ASTEROID_WHITE_NUMROWS = 6;
const int ASTEROID_GOLD_WIDTH = 85;
const int ASTEROID_GOLD_HEIGHT = 100;
const int ASTEROID_GOLD_NUMCOLS = 5;
const int ASTEROID_GOLD_NUMROWS = 6;

// HEALTH
const int NUMBER_LIVES = 3;
const int LIVES_WIDTH = 46;
const int LIVES_HEIGHT = 46;
const Vector2D LIVES_POSITION = { 10, WIN_HEIGHT/LIVES_HEIGHT };

// BULLET
const int BULLET_WIDTH = 5;
const int BULLET_HEIGHT = 20;
#endif