#pragma once
#include "../game/Game.h"
#include "../game/GameStateMachine.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/fighterComponents/Health.h"
#include "../sdlutils/InputHandler.h"

class PauseState : public Manager {
private:
	Entity* fighter;
	Entity* pressToContinue;
	Game* game;
public:

	// Constructora
	PauseState(Game* game);
	// Destructora
	~PauseState();
	// Recoge el input del usuario
	void handleEvent();
};