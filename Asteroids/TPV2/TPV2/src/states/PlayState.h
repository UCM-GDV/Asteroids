#pragma once
#ifndef PLAY_STATE_H_
#define PLAY_STATE_H_
#include "../game/GameState.h"

class PlayState : public GameState {
public:
	// Constructora
	PlayState(Game* _game);
	// Destructora
	~PlayState();
};
#endif