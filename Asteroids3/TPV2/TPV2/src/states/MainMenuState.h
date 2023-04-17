#pragma once
#include "../ecs/Manager.h"	
#include "../systems/GameCtrlSystem.h"
#include "../systems/RenderSystem.h"

#include <SDL_net.h>

class MainMenuState : public Manager {
private:
	FighterSystem* fighterSys_;
	GameCtrlSystem* gameCtrlSys_;
	RenderSystem* renderSys_;
public:
	// Constructora
	MainMenuState();
	// Destructora
	~MainMenuState();
	// Servidor
	void server(int port);
	// Cliente 
	void client(char* host, int port);
};