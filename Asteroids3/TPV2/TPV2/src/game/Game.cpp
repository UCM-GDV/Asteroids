#include "Game.h"
#include "../sdlutils/macros.h"
using namespace std;

// Constructora
Game::Game() {
	// Crea la ventana
	SDLUtils::init(GAME_NAME, WIN_WIDTH, WIN_HEIGHT,
		"resources/config/asteroid.resources.json");

	// Instancia  el SDL
	sdl = SDLUtils::instance();
	window = sdl->window();
	sdl->showCursor();

	exit = false;

	// Anade los nuevos estados
	GameStateMachine::instance()->pushState(new MainMenuState());
}

// Destructora
Game::~Game() {
	SDL_DestroyRenderer(SDLUtils::instance()->renderer());
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// Bucle de juego
void Game::run() {
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();
    SDL_Event e;

	while (!exit) {
		refresh();
		
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime >= DELAY_TIME) {
			update();
			startTime = SDL_GetTicks();
		}
	}

	GameStateMachine::instance()->clearStates();
}

// Actualiza el juego
void Game::update() {
	if (!GameStateMachine::instance()->isEmpty()) {
		GameStateMachine::instance()->currentState()->update();
		GameStateMachine::instance()->clearStatesToErase();
	}
	else exit = true;
}

// Actualiza el juego en función del estado actual
void Game::refresh() {
	if (!GameStateMachine::instance()->isEmpty()) {
		GameStateMachine::instance()->currentState()->refresh();
	}
}
