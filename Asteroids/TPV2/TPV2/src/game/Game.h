#pragma once
#ifndef GAME_H_
#define GAME_H_
#include <SDL.h>
#include <unordered_map>
#include <fstream>
#include "constants.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "GameStateMachine.h"
#include "../states/PauseState.h"
#include "../states/PlayState.h"
#include "../sdlutils/InputHandler.h"
using namespace std;

class Game {
private:
	SDLUtils* sdl = nullptr;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	InputHandler* inputHandler = nullptr;
	GameStateMachine* gameStateMachine = nullptr;
	bool exit;
public:
	// Constructora
	Game();
	// Destructora
	~Game();
	// Ejecuta el juego
	void run();
	// Dibuja el juego
	void render() const;
	// Actualiza el juego
	void update();
	// Actualiza el juego en función al evento actual
	void refresh();
	void handleEvents();
	// Devuelve un renderer
	SDL_Renderer* getRenderer();
};
#endif
