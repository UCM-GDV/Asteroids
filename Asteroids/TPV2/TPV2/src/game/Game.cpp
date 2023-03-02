#include "Game.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/macros.h"
using namespace std;

// Constructora
Game::Game() {
	// Crea la ventana
	SDLUtils::init(GAME_NAME, WIN_WIDTH, WIN_HEIGHT,
		"resources/config/game.resources.json");

	sdl = SDLUtils::instance();
	renderer = sdl->renderer();
	window = sdl->window();
	sdl->showCursor();
	
	inputHandler = InputHandler::instance();

	exit = false;
	GameStateMachine::instance()->pushState(new PlayState());
	GameStateMachine::instance()->pushState(new PauseState());

}

// Destructora
Game::~Game() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// Bucle de juego
void Game::run() {
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();

	while (!exit) {
		refresh();
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime >= DELAY_TIME) {
			update();
			render();
			startTime = SDL_GetTicks();
		}
		handleEvents();
	}
	GameStateMachine::instance()->clearStates();
}

// Dibuja el juego
void Game::render() const {
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 30, 50, 0);
	SDL_RenderClear(renderer);
	GameStateMachine::instance()->currentState()->render();
	SDL_RenderPresent(renderer);
}

// Actualiza el juego
void Game::update() {
	GameStateMachine::instance()->currentState()->update();
	GameStateMachine::instance()->clearStatesToErase();
}

// Actualiza el juego en función al evento actual
void Game::refresh() {
	inputHandler->refresh();
	GameStateMachine::instance()->currentState()->refresh();
}

//Controla los eventos
void Game::handleEvents() {
	GameStateMachine::instance()->currentState()->handleEvent();
}

SDL_Renderer* Game::getRenderer() { return sdlutils().renderer(); }