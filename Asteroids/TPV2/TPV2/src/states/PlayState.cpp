#include "PlayState.h"

// Constructora
PlayState::PlayState(Game* _game): Manager(), game(_game)  {

	fighter = new Fighter(game);
	addEntity(fighter);
	//addEntity(new Asteroid(game));
	
}

// Destructora
PlayState::~PlayState() {

}
void PlayState::addBullet() {
	addEntity(new Bullet(fighter));
}