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
	RenderSystem* renderSys_;

	Entity* pressToStartEntity;
	Entity* resultEntity;
public:
	// Constructora
	EndState(int resultString);
};