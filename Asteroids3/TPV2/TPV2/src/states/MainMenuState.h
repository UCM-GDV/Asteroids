#pragma once
#include "../ecs/Manager.h"	
#include "../systems/GameCtrlSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/NetWorkSystem.h"
#include <SDL_net.h>
#include <vector>
#include "../ecs/Entity.h"

class MainMenuState : public Manager {
private:
	FighterSystem* fighterSys_;
	GameCtrlSystem* gameCtrlSys_;
	RenderSystem* renderSys_;
	char* ip;
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
	void server(const int port);
	// Cliente 
	void client(const char* host, const int port);

	// Devuelve la ip
	inline const char* getIp() { return ip; }
	// Establece la ip
	inline void setIp(string ip_) { ip = &ip_[0]; cout << ip << "asdfgh"; }
	
	// UI
	void createHostButton();
	void createClientButton();
	void createEnterButton(bool player);
	void createNameTextBox();
};