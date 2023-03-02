#pragma once
#ifndef GAME_H_
#define GAME_H_
#include <SDL.h>
#include <unordered_map>
#include <fstream>
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "GameStateMachine.h"
#include "../states/PauseState.h"
#include "../states/PlayState.h"
#include "../states/EndState.h"
#include "../sdlutils/InputHandler.h"
using namespace std;

class Game {
private:
	SDLUtils* sdl = nullptr;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	InputHandler* inputHandler = nullptr;
	bool exit;
	unordered_map<string,Texture*> texts;
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
	// Actualiza el juego en funci�n del estado actual
	void refresh();
	// Maneja los eventos del estado actual
	void handleEvents();
	// Devuelve el renderer
	inline SDL_Renderer* getRenderer() { return sdlutils().renderer(); }
	// Devuelve la textura de texto deseado
	inline Texture* getText(string text) { return texts[text]; }
	// Sale del juego
	inline void exitGame() { exit = true; }
};
#endif
