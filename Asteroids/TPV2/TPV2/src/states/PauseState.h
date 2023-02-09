#pragma once
#ifndef PAUSE_STATE_H_
#define PAUSE_STATE_H_
#include "../game/GameState.h"

class PauseState : public GameState {
public:
	// Constructora
	PauseState(Game* _game);
	// Destructora
	~PauseState();
};
#endif