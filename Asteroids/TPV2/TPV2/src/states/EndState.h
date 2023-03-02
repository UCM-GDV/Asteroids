#pragma once
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "PauseState.h"
//#include "../components/Transform.h"
//#include "../components/Image.h"
#include "../sdlutils/InputHandler.h"
#include "../game/GameStateMachine.h"

class EndState : public Manager {
private:
	Entity* fighter;
public:

	// Constructora
	EndState(string result);
	// 
	void handleEvent();
	// Destructora
	~EndState();
};