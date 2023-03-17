#pragma once
#include "../ecs/Manager.h"	
#include "../sdlutils/InputHandler.h"
#include "../systems/RenderSystem.h"
#include "../systems/FighterSystem.h"

class EndState : public Manager {
private:
	Entity* fighter;
	Entity* result;
	Entity* pressToStart;

	RenderSystem* renderSystem;
public:

	// Constructora
	EndState(string resultString);
	// Destructora
	virtual ~EndState();
	// Recoge el input del usuario
	//void handleEvent();
};