#pragma once
#include "../ecs/Manager.h"	
#include "../sdlutils/InputHandler.h"
#include "../systems/RenderSystem.h"
#include "../systems/FighterSystem.h"
#include "../systems/GameCtrlSystem.h"
class EndState : public Manager {
private:
	FighterSystem* fighterSys_;
	GameCtrlSystem* gameCtrlSys_;
	RenderSystem* renderSystem;
public:

	// Constructora
	EndState(string resultString);
	// Destructora
	virtual ~EndState();
	// Recoge el input del usuario
	//void handleEvent();
};