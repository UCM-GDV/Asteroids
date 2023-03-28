#include "PlayState.h"

// Constructora
PlayState::PlayState(): Manager(), bullet(nullptr) {
	// Sistemas
	fighterSys_ = addSystem<FighterSystem>(1);
	asteroidsSys_ = addSystem<AsteroidsSystem>();
	bulletSys_ = addSystem<BulletSystem>();
	collisionsSys_ = addSystem<CollisionsSystem>();
	
	gameCtrlSys_ = addSystem<GameCtrlSystem>();
	renderSys_ = addSystem<RenderSystem>();
}

// Destructora
PlayState::~PlayState() {}

// Anade bala a la escena dependiendo de la posicion del fighter
//void PlayState::addBullet() {
//	Vector2D bPos, bVel;
//	bPos = fighterTransform->getPos()
//		+ Vector2D(FIGHTER_HALF_WIDTH, FIGHTER_HALF_HEIGHT)
//		- Vector2D(0.0f, FIGHTER_HEIGHT / 2.0f + 5.0f + 12.0f).rotate(fighterTransform->getR())
//		- Vector2D(2.0f, 10.0f);
//	bVel = Vector2D(0.0f, -1.0f).rotate(fighterTransform->getR()) * (fighterTransform->getVel().magnitude() + 5.0f);
//
//	bullet = new Entity();
//	bullet->addComponent<Transform>(_TRANSFORM, bPos, bVel, BULLET_WIDTH, BULLET_HEIGHT, fighterTransform->getR());
//	bullet->addComponent<Image>(_IMAGE, &SDLUtils::instance()->images().at("Bullet"));
//	bullet->addComponent<DisableOnExit>(_DISABLEONEXIT);
//	addEntity(bullet, _grp_BULLETS);
//}

// Para el juego
void PlayState::pauseGame() {
	//GameStateMachine::instance()->pushState(new PauseState());
}

// Fin del juego
void PlayState::endGame(string result) {
   // GameStateMachine::instance()->pushState(new EndState( result));
}