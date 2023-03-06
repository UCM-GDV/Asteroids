#pragma once
#include "../game/Game.h"
#include "../game/GameStateMachine.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "PauseState.h"

class EndState : public Manager {
private:
	Entity* fighter;
	Entity* result;
	Entity* pressToStart;
	Game* game;
public:

	// Constructora
	EndState(Game* game, string resultString);
	// Destructora
	virtual ~EndState();
	// Recoge el input del usuario
	void handleEvent();
};