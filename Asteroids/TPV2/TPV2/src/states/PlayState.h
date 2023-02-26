#pragma once
#ifndef PLAY_STATE_H_
#define PLAY_STATE_H_
#include "../ecs/Manager.h"
#include "../entities/fighter.h"
#include "../entities/asteroid.h"

class PlayState : public Manager {
private:
	Game* game = nullptr;
	Fighter* fighter;
public:
	// Constructora
	PlayState(Game* _game);
	// Destructora
	~PlayState();
	// 
	void addBullet();
};
#endif