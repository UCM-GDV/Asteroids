#pragma once
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"/*
#include "../systems/RenderSystem.h"*/
#include "../systems/FighterSystem.h"

class PauseState : public Manager {
private:
	Entity* fighter;
	Entity* pressToContinue;
	//Game* game;
	//RenderSystem* renderSystem;
public:

	// Constructora
	PauseState();
	// Destructora
	~PauseState();
	// Recoge el input del usuario
	void handleEvent();
};