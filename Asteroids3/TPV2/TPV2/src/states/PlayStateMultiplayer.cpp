#include "./PlayStateMultiplayer.h"

// Constructora
PlayStateMultiPlayer::PlayStateMultiPlayer(): Manager() {
	// Sistemas
	addSystem<NetworkSystem>(1);
	addSystem<FighterSystem>(1);
	addSystem<GameCtrlSystem>(1);
	addSystem<BulletSystem>();
	addSystem<CollisionsSystem>();
	 addSystem<RenderSystem>(1);

}

// Destructora
PlayStateMultiPlayer::~PlayStateMultiPlayer() {}