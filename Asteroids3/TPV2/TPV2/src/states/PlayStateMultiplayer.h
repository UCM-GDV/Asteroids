#pragma once
#include "../ecs/Manager.h"
// Sistemas
#include "../systems/BulletSystem.h"
#include "../systems/CollisionsSystem.h"
#include "../systems/FighterSystem.h"
#include "../systems/NetWorkSystem.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/RenderSystem.h"
#include "../sdlutils/InputHandler.h"
#include "../systems/NetWorkSystem.h"
class PlayState : public Manager {
private:
	// Entidades
	Entity* bullet;
	
	// Sistemas
	BulletSystem* bulletSys_;
	NetworkSystem* networkSys_;
	CollisionsSystem* collisionsSys_;
	FighterSystem* fighterSys_;
	GameCtrlSystem* gameCtrlSys_;
	RenderSystem* renderSys_;
public:
	// Constructora
	PlayState();
	// Destructora
	~PlayState();
	// Anade bala a la escena dependiendo de la posicion del fighter
	//void addBullet();
    // Recoge el input del usuario
	//void handleEvent();
	
	// Para el juego
	void pauseGame();
	// Fin del juego
    void endGame(string result);
};