#pragma once
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../systems/RenderSystem.h"
#include "../systems/FighterSystem.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/RenderSystem.h"

class PauseState : public Manager {
private:
	FighterSystem* fighterSys_;
	GameCtrlSystem* gameCtrlSys_;
	RenderSystem* renderSys_;
public:

	// Constructora
	PauseState();
	// Destructora
	~PauseState();
};