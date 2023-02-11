#pragma once
#ifndef PLAY_STATE_H_
#define PLAY_STATE_H_
#include "../ecs/Manager.h"

class PlayState : public Manager {
public:
	// Constructora
	PlayState(Game* _game);
	// Destructora
	~PlayState();
};
#endif