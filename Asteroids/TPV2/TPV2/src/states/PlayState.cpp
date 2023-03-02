#include "PlayState.h"

// Constructora
PlayState::PlayState(Game* game): Manager(), bullet(nullptr), game(game) {

	// FIGHTER
	fighter = new Entity();
	fighter->setContext(this);
	fighterTransform = fighter->addComponent<Transform>(_TRANSFORM, Vector2D(WIN_HALF_WIDTH, WIN_HALF_HEIGHT), FIGHTER_VELOCITY, FIGHTER_WIDTH, FIGHTER_HEIGHT, FIGHTER_ROTATION);
	fighter->addComponent<Image>(_IMAGE, &SDLUtils::instance()->images().at("Fighter"));
	fighter->addComponent<Health>(_HEALTH);
	fighterControl = fighter->addComponent<FighterControl>(_FIGHTERCONTROL);
	fighter->addComponent<DeAcceleration>(_DEACCELERATION);
	fighterGun = fighter->addComponent<Gun>(_GUN);
	fighter->addComponent<ShowAtOppositeSide>(_SHOWATOPPOSIDESIDE);
	addEntity(fighter);

	AsteroidsManager::instance()->init(this);
	AsteroidsManager::instance()->createAsteroids(ASTEROIDS_INITIAL_NUMBER);
	CollisionsManager::instance()->init(this);
}

// Destructora
PlayState::~PlayState() {
	fighter = nullptr;
	fighterTransform = nullptr;
	fighterGun = nullptr;
	fighterControl = nullptr;
}

// Control del fighter y de los disparos
void PlayState::handleEvent() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		fighterControl->handleEvent(event);
		fighterGun->handleEvent(event);
		if (InputHandler::instance()->isKeyDown(SDLK_ESCAPE)) {
			pauseGame();
		}
	}
}

// Anade bala a la escena dependiendo de la posicion del fighter
void PlayState::addBullet() {
	Vector2D bPos, bVel;
	bPos = fighterTransform->getPos()
		+ Vector2D(FIGHTER_HALF_WIDTH, FIGHTER_HALF_HEIGHT)
		- Vector2D(0.0f, FIGHTER_HEIGHT / 2.0f + 5.0f + 12.0f).rotate(fighterTransform->getR())
		- Vector2D(2.0f, 10.0f);
	bVel = Vector2D(0.0f, -1.0f).rotate(fighterTransform->getR()) * (fighterTransform->getVel().magnitude() + 5.0f);

	bullet = new Entity();
	bullet->addComponent<Transform>(_TRANSFORM, bPos, bVel, BULLET_WIDTH, BULLET_HEIGHT, fighterTransform->getR());
	bullet->addComponent<Image>(_IMAGE, &SDLUtils::instance()->images().at("Bullet"));
	bullet->addComponent<DisableOnExit>(_DISABLEONEXIT);
	addEntity(bullet, _grp_BULLETS);
}

// Actualiza el vector de entidades, anade asteroides y comprueba las colisiones
void PlayState::update() {
	Manager::update();
	AsteroidsManager::instance()->addAsteroidFrequently();
	CollisionsManager::instance()->checkCollision();
}

// Para el juego
void PlayState::pauseGame() {
	GameStateMachine::instance()->pushState(new PauseState(game));
}

// Fin del juego
void PlayState::endGame(string result) {
    GameStateMachine::instance()->pushState(new EndState(game, result));
}