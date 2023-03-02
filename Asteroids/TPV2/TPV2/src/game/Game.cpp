#include "Game.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/macros.h"
using namespace std;

// Constructora
Game::Game() {
	// Crea la ventana
	SDLUtils::init(GAME_NAME, WIN_WIDTH, WIN_HEIGHT,
		"resources/config/asteroid.resources.json");

	// Instancia  el SDL
	sdl = SDLUtils::instance();
	// Coge el redenderer 
	renderer = sdl->renderer();
	window = sdl->window();
	sdl->showCursor();
	// Instancia el inputHandle
	inputHandler = InputHandler::instance();
	exit = false;

	// Carga las texturas de los textos
	texts[PRESS_TO_CONTINUE_TEXT] = new Texture(renderer, PRESS_TO_CONTINUE_TEXT, sdl->fonts().at("ARIAL24"), build_sdlcolor(0x112233ff), build_sdlcolor(0xffffffff));
	texts[PRESS_TO_START_TEXT] = new Texture(renderer, PRESS_TO_START_TEXT, sdl->fonts().at("ARIAL24"), build_sdlcolor(0x112233ff), build_sdlcolor(0xffffffff));
	texts[GAME_OVER_LOSE_TEXT] = new Texture(renderer, GAME_OVER_LOSE_TEXT, sdl->fonts().at("ARIAL24"), build_sdlcolor(0xff0000));
	texts[GAME_OVER_WIN_TEXT] = new Texture(renderer, GAME_OVER_WIN_TEXT, sdl->fonts().at("ARIAL24"), build_sdlcolor(0xff0000));

	// Añade los nuevos estados
	GameStateMachine::instance()->pushState(new PlayState(this));
	GameStateMachine::instance()->pushState(new PauseState(this));
}

// Destructora
Game::~Game() {

	// Elimina las texturas de texts
	for (auto it = texts.begin(); it != texts.end(); ++it) {
		delete it->second;
	}

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

// Actualiza el juego en función del estado actual
void Game::refresh() {
	inputHandler->refresh();
	GameStateMachine::instance()->currentState()->refresh();
}

// Maneja los eventos del estado actual
void Game::handleEvents() {
	GameStateMachine::instance()->currentState()->handleEvent();
}