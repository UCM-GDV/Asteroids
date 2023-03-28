#pragma once
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../systems/RenderSystem.h"
#include "../systems/FighterSystem.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/RenderSystem.h"

class PauseState : public Manager {
private:
	//Entity* fighter;
	//Entity* pressToContinue;

	FighterSystem* fighterSys_;
	GameCtrlSystem* gameCtrlSys_;
	RenderSystem* renderSys_;
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