#pragma once
#ifndef GAME_H_
#define GAME_H_
#include <SDL.h>
#include "constants.h"
#include "../sdlutils/Texture.h"
#include "GameStateMachine.h"
#include "../states/PauseState.h"
#include "../states/PlayState.h"
using namespace std;

using TextureName = string;

typedef struct {
	string filename;
	uint hframes, vframes;
} TextureDescription;

class Game {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
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
	// Devuelve un renderer
	SDL_Renderer* getRenderer();
	// Devuelve la textura pedida
	//Texture* getTexture(TextureName texture) const;
};
#endif
