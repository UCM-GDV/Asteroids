#include "PauseState.h"

// Constructora
PauseState::PauseState(Game* _game) : Manager(), game(_game) {
	
	addEntity(new Fighter(game));
}

// Destructora
PauseState::~PauseState() {
}