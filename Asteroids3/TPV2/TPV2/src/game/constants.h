#pragma once
#include <SDL.h>
#include <iostream>
#include "../utils/Vector2D.h"
using namespace std;

// BASICS
const Vector2D VECTOR_ZERO = Vector2D(0, 0);

// ONLINE
const int MAX_PACKET_SIZE = 512;
const int PORT = 9999;

// WINDOW
const string GAME_NAME = "Asteroids";
const float WIN_WIDTH = 1000;
const float WIN_HEIGHT = 600;
const float WIN_HALF_WIDTH = WIN_WIDTH / 2;
const float WIN_HALF_HEIGHT = WIN_HEIGHT / 2;
const SDL_Rect FULLWINDOW = { 0, 0, WIN_WIDTH, WIN_HEIGHT };

// FRAME TIMES
const double FRAME_TIME = 30;
const int DELAY_TIME = 2;

// TEXTURES
const string TEXTURES_FILE = "resources/config/textures.txt";
const int NUM_TEXTURES = 19;
const int BLOCK_NUMB = 3;
const int DIGITS_NUMB = 4;

// COLORS
const unsigned long COLOR_BLACK = 0x00000000;
const unsigned long COLOR_WHITE = 0xffffffff;
const unsigned long COLOR_GREEN = 0x00ff00ff;
const unsigned long COLOR_RED = 0xff000000;

// BUTTONS
const int BUTTON_WIDTH = 400;
const int BUTTON_HEIGHT = 40;
const Vector2D ONEPLAYER_BUTTON_POSITION = Vector2D(WIN_HALF_WIDTH - BUTTON_WIDTH / 2, WIN_HEIGHT / 3);
const Vector2D MULTIPLAYER_BUTTON_POSITION = Vector2D(WIN_HALF_WIDTH - BUTTON_WIDTH / 2, WIN_HEIGHT / 2);
//const Vector2D HOST_BUTTON_POSITION = Vector2D(WIN_HALF_WIDTH - BUTTON_WIDTH / 2 - 5, WIN_HEIGHT / 2 - BUTTON_HEIGHT / 2);
//const Vector2D CLIENT_BUTTON_POSITION = Vector2D(WIN_HALF_WIDTH + 5, WIN_HEIGHT / 2 - BUTTON_HEIGHT / 2);
const string ONEPLAYER_TEXT = "ONE PLAYER";
const string MULTIPLAYER_TEXT = "MULTIPLAYER";
const string HOST_TEXT = "HOST";
const string CLIENT_TEXT = "CLIENT";
const string NAME_TEXT_BOX = "ESCRIBE TU NOMBRE...";
const string ENTER_TEXT = "ENTER";
const string WAITING_TEXT = "Waiting for other player...";
const string IP_TEXT = "ESCRIBE LA IP...";

// FIGHTER
const float FIGHTER_WIDTH = 50;
const float FIGHTER_HEIGHT = 50;
const float FIGHTER_HALF_WIDTH = FIGHTER_WIDTH / 2;
const float FIGHTER_HALF_HEIGHT = FIGHTER_HEIGHT / 2;
const Vector2D FIGHTER_VELOCITY = Vector2D(0, 0);
const int FIGHTER_ROTATION_SPEED = 140;
const float FIGHTER_ROTATION = 0;
const Vector2D SPEED_LIMIT = Vector2D(0, 3.0f);

const float FIGHTER_POS_WIDTH = WIN_WIDTH / 2;
const float FIGHTER_POS_HEIGHT = WIN_HEIGHT / 2;

const Vector2D FIGHTER_POS = { WIN_HALF_WIDTH, WIN_HALF_HEIGHT };
const Vector2D FIGHTER_1_POS = { 50 , WIN_HEIGHT / 2 };
const Vector2D FIGHTER_2_POS = { WIN_WIDTH - 50 , WIN_HEIGHT / 2 };

// ASTEROID
const int ASTEROIDS_INITIAL_NUMBER = 10;
const int ASTEROIDS_MAX_NUMBER = 30;
const int ASTEROIDS_DELAY_TIME = 5000;
const int ASTEROID_WHITE_FRAME_WIDTH = 85;
const int ASTEROID_WHITE_FRAME_HEIGHT = 100;
const int ASTEROID_WHITE_NUMCOLS = 5;
const int ASTEROID_WHITE_NUMROWS = 6;
const int ASTEROID_YELLOW_FRAME_WIDTH = 85;
const int ASTEROID_YELLOW_FRAME_HEIGHT = 100;
const int ASTEROID_YELLOW_NUMCOLS = 5;
const int ASTEROID_YELLOW_NUMROWS = 6;

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
const Vector2D GAME_OVER_TEXT_POSITION = Vector2D(WIN_HALF_WIDTH - TEXT_WIDTH / 2, WIN_HEIGHT / 3);
const string PRESS_TO_CONTINUE_TEXT = "Press space to continue";
const string PRESS_TO_START_TEXT = "Press space to start";
const string GAME_OVER_LOSE_TEXT = "Game Over: Loser!";
const string GAME_OVER_WIN_TEXT = "Game Over: Win!";