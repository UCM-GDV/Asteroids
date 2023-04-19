#pragma once
#include "../ecs/Manager.h"	
#include "../systems/GameCtrlSystem.h"
#include "../systems/RenderSystem.h"
#include <SDL_net.h>
#include <vector>
#include "../ecs/Entity.h"

class MainMenuState : public Manager {
private:
	FighterSystem* fighterSys_;
	GameCtrlSystem* gameCtrlSys_;
	RenderSystem* renderSys_;	
public:
	Entity* onePlayerButton;
	Entity* multiPlayerButton;
	Entity* hostButton;
	Entity* clientButton;
	Entity* enterButton;
	Entity* nameTextBox;
	Entity* waitingText;
	Entity* ipTextBox;

	// Constructora
	MainMenuState();
	// Destructora
	~MainMenuState();
	// Servidor
	void server(int port);
	// Cliente 
	void client(char* host, int port);

	// UI
	void createHostButton();
	void createClientButton();
	void createEnterButton(bool player);
	void createNameTextBox();
};