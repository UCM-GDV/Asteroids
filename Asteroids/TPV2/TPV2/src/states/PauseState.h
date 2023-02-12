#pragma once
#ifndef PAUSE_STATE_H_
#define PAUSE_STATE_H_
#include "../ecs/Manager.h"
#include "../entities/fighter.h"
#include "../entities/asteroid.h"

class PauseState : public Manager {
private:
	Game* game = nullptr;
public:
	// Constructora
	PauseState(Game* _game);
	// Destructora
	~PauseState();
};
#endif