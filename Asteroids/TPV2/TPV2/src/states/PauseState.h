#pragma once
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/fighterComponents/Health.h"
#include "../sdlutils/InputHandler.h"
#include "../game/GameStateMachine.h"

class PauseState : public Manager {
private:
	Entity* fighter;
public:

	// Constructora
	PauseState();
	void handleEvent();
	// Destructora
	~PauseState();
};