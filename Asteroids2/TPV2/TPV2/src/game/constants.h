#pragma once
#include <SDL.h>
#include <iostream>
#include "../utils/Vector2D.h"
using namespace std;

// BASICS
const Vector2D VECTOR_ZERO = Vector2D(0, 0);

// WINDOW
const string GAME_NAME = "Asteroids";
const float WIN_WIDTH = 1000;
const float WIN_HEIGHT = 600;
const float WIN_HALF_WIDTH = WIN_WIDTH / 2;
const float WIN_HALF_HEIGHT = WIN_HEIGHT / 2;
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
const float FIGHTER_HALF_WIDTH = FIGHTER_WIDTH / 2;
const float FIGHTER_HALF_HEIGHT = FIGHTER_HEIGHT / 2;
const Vector2D FIGHTER_VELOCITY = Vector2D(0, 0);
const int FIGHTER_ROTATION_SPEED = 140;
const float FIGHTER_ROTATION = 0;
const Vector2D SPEED_LIMIT = Vector2D(0, 3.0f);

// ASTEROID
const int ASTEROIDS_INITIAL_NUMBER = 10;
const int ASTEROIDS_MAX_NUMBER = 30;
const int ASTEROIDS_DELAY_TIME = 5000;
const int ASTEROID_WHITE_FRAME_WIDTH = 85;
const int ASTEROID_WHITE_FRAME_HEIGHT = 100;
const int ASTEROID_WHITE_NUMCOLS = 5;
const int ASTEROID_WHITE_NUMROWS = 6;
const int ASTEROID_GOLD_FRAME_WIDTH = 85;
const int ASTEROID_GOLD_FRAME_HEIGHT = 100;
const int ASTEROID_GOLD_NUMCOLS = 5;
const int ASTEROID_GOLD_NUMROWS = 6;

// HEALTH
const int NUMBER_LIVES = 3;
const int LIVES_WIDTH = 46;
const int LIVES_HEIGHT = 46;
const Vector2D LIVES_POSITION = Vector2D(10, WIN_HEIGHT/LIVES_HEIGHT);

// BULLET
const int BULLET_WIDTH = 5;
const int BULLET_HEIGHT = 20;

// TEXTS
const int TEXT_WIDTH = 400;
const int TEXT_HEIGHT = 40;
const Vector2D TEXT_POSITION = Vector2D(WIN_HALF_WIDTH - TEXT_WIDTH / 2, WIN_HEIGHT * 2 / 3);
const string PRESS_TO_CONTINUE_TEXT = "Press space to continue";
const string PRESS_TO_START_TEXT = "Press space to start";
const string GAME_OVER_LOSE_TEXT = "Game Over: Loser!";
const string GAME_OVER_WIN_TEXT = "Game Over: Win!";