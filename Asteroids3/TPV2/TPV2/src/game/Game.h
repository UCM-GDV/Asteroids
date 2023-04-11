#pragma once
#include <SDL.h>
#include <fstream>
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "GameStateMachine.h"
#include "../states/PauseState.h"
#include "../states/PlayState.h"
#include "../states/EndState.h"
using namespace std;

class Game {
private:
	SDLUtils* sdl = nullptr;
	SDL_Window* window = nullptr;
	bool exit;
public:
	// Constructora
	Game();
	// Destructora
	~Game();
	// Ejecuta el juego
	void run();
	// Actualiza el juego
	void update();
	// Actualiza el juego en función del estado actual
	void refresh();
	// Sale del juego
	inline void exitGame() { exit = true; }
};
