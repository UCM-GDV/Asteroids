#include "Game.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
using namespace std;

// Constructora
Game::Game() {
	/*SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) {
		throw "Could not load the window.";
	}*/

	// Crea la ventana
	SDLUtils::init();
	renderer = SDLUtils::instance()->renderer();
	window = SDLUtils::instance()->window();

	// Carga de texturas
	/*
	ifstream file(TEXTURES_FILE);
	if (!file) {
		file.close();
		throw "Could not find file: " + TEXTURES_FILE;
	}
	try {
		string key, path; uint hframes, vframes;
		file >> key;
		while (!file.eof()) {
			file >> path >> vframes >> hframes;
			texturesMap[key] = new Texture(renderer, path, hframes, vframes);
			file >> key;
		}
		file.close();
	}
	catch (string error) {
		file.close();
		throw "File format error. Invalid textures file. " + error;
	}
	*/

	exit = false;
	gameStateMachine = new GameStateMachine();
	gameStateMachine->pushState(new PauseState(this));
	
}

// Destructora
Game::~Game() {
	delete(gameStateMachine);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// Bucle de juego
void Game::run() {
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();

	while (!exit) {
		update();
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime >= DELAY_TIME) {
			render();
			startTime = SDL_GetTicks();
		}
		refresh();
	}
	gameStateMachine->clearStates();
}

// Dibuja el juego
void Game::render() const {
	SDL_RenderClear(renderer);
	gameStateMachine->currentState()->render();
	SDL_RenderPresent(renderer);
}

// Actualiza el juego
void Game::update() {
	gameStateMachine->currentState()->update();
	gameStateMachine->clearStatesToErase();
}

// Actualiza el juego en función al evento actual
void Game::refresh() {
	gameStateMachine->currentState()->refresh();
}

SDL_Renderer* Game::getRenderer() { return SDLUtils::instance()->renderer(); }

/*
Texture* getTexture(TextureName texture) const {
	return texture
}*/
