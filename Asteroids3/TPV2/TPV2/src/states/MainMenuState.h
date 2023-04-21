#pragma once
#include "../ecs/Manager.h"
#include "../systems/FighterSystem.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/RenderSystem.h"
#include "../ecs/Entity.h"

class MainMenuState : public Manager {
private:
	FighterSystem* fighterSys_;
	GameCtrlSystem* gameCtrlSys_;
	RenderSystem* renderSys_;
public:
	Entity* onePlayerButton;
	Entity* multiPlayerButton;
	
	// Constructora
	MainMenuState();
	// Destructora
	~MainMenuState();

	void goToPlayState();
	void goToPlayStateMultiplayer();
};