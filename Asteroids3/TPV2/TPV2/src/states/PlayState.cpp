#include "PlayState.h"

// Constructora
PlayState::PlayState(): Manager(){
	// Sistemas
	addSystem<FighterSystem>(1);
	addSystem<GameCtrlSystem>(1);
	addSystem<AsteroidsSystem>();
	addSystem<BulletSystem>();
	addSystem<CollisionsSystem>();
	addSystem<RenderSystem>(1);
}

// Destructora
PlayState::~PlayState() {}
