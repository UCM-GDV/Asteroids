#include "AsteroidsSystem.h"

// Destructora
AsteroidsSystem::~AsteroidsSystem() {
	asteroid = nullptr;
}

// Inicializa el sistema
void AsteroidsSystem::initSystem() {
	numOfAsteroids_ = 0;
	startTime = SDL_GetTicks();
	asteroid = nullptr;
}

// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void AsteroidsSystem::receive(const Message& m) {
	switch (m.id) {
		case _m_FIGTHER_ASTEROID_COLLIDED: onRoundOver(); break;
		default: break;
	}
}

// Si el juego está parado no hacer nada, en otro caso mover los asteroides como
// en la práctica 1 y generar 1 asteroide nuevo cada 5 segundos (aparte
// de los 10 al principio de cada ronda).
void AsteroidsSystem::update() {

	// addAsteroidFrequently()
	// Genera un asteroide nuevo cada 5 segundos 
	uint32_t frameTime = SDL_GetTicks() - startTime;
	if (frameTime >= ASTEROIDS_DELAY_TIME) {
		createAsteroids(1);
		startTime = SDL_GetTicks();
	}

	// Movimiento de los asteroides
	for (auto asteroid : mngr_->getEntities(_grp_ASTEROIDS_WHITE)) {
		auto tr = mngr_->getComponent<Transform>(asteroid);
		tr->position_ = tr->position_ + tr->velocity_;
		//tr->rotation_ += 5.0f;
	}
	for (auto asteroid : mngr_->getEntities(_grp_ASTEROIDS_YELLOW)) {
		auto tr = mngr_->getComponent<Transform>(asteroid);
		tr->position_ = tr->position_ + tr->velocity_;
		//tr->rotation_ += 5.0f;
	}

	// SHOWATOPPOSITESIDE
	//if (transform->getPos().getX() < -(FIGHTER_WIDTH)) {
	//	transform->setPos(Vector2D(WIN_WIDTH, transform->getPos().getY()));
	//}
	//else if (transform->getPos().getX() > (WIN_WIDTH + FIGHTER_WIDTH)) {
	//	transform->setPos(Vector2D(0, transform->getPos().getY()));
	//}
	//if (transform->getPos().getY() < -(FIGHTER_HEIGHT)) {
	//	transform->setPos(Vector2D(transform->getPos().getX(), WIN_HEIGHT));
	//}
	//else if (transform->getPos().getY() > (WIN_HEIGHT + FIGHTER_HEIGHT)) {
	//	transform->setPos(Vector2D(transform->getPos().getX(), 0));
	//}
}

// Para gestionar el mensaje de que ha acabado la ronda. Desactivar todos los
// asteroides, y desactivar el sistema.
void AsteroidsSystem::onRoundOver() {
	// Desactivar todos los asteroides
	destroyAllAsteroids();
}

// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema y
// añadir los asteroides iniciales (como en la práctica 1).
void AsteroidsSystem::onRoundStart() {
	// Anade los asteroides iniciales
	createAsteroids(ASTEROIDS_INITIAL_NUMBER);
}

// Crea n asteroides
void AsteroidsSystem::createAsteroids(int n) {
	//for (int i = 0; i < n; i++) {
	//	if (numOfAsteroids_ < ASTEROIDS_MAX_NUMBER) {
	//		// Elige una generacion aleatoria entre 1 y 3
	//		int g = sdlutils().rand().nextInt(1, 4);
	//		float width, height;
	//		width = height = 10.0f + 5.0f * g;
	//		Vector2D p = choosePosition(width, height);
	//		Vector2D v = chooseVelocity(p);

	//		// Crea un tipo de asteroide dependiendo de una probabilidad
	//		(sdlutils().rand().nextInt(0, 10) < 3) ? createYellowAsteroid(p, v, width, height, g) : createWhiteAsteroid(p, v, width, height, g);
	//	}
	//}
}

// Destruye todos los asteroides pertenecientes al _grp_ASTEROIDS de las entidades de la escena
void AsteroidsSystem::destroyAllAsteroids() {
	for (auto& asteroid : mngr_->getEntities(_grp_ASTEROIDS_WHITE)) {
		asteroid->setAlive(false);
	}
	for (auto& asteroid : mngr_->getEntities(_grp_ASTEROIDS_YELLOW)) {
		asteroid->setAlive(false);
	}
	numOfAsteroids_ = 0;
}

// Para gestionar el mensaje de que ha habido un choque de un asteroide con una
// bala. Desactivar el asteroide “a” y crear 2 asteroides como en la práctica 1,
// y si no hay más asteroides enviar un mensaje correspondiente.
void AsteroidsSystem::onCollision_AsteroidBullet(Entity* a) {
	//sdlutils().soundEffects().at("asteroidexplosion").play();
	//// Lo desactiva 
	//a->setAlive(false);
	//numOfAsteroids_--;
	//Generations* g = a->getComponent<Generations>(_GENERATIONS);
	//g->decreaseGeneration();
	//Transform* at = a->getComponent<Transform>(_TRANSFORM);

	//int gens = g->getGenerations();
	//float width, height;
	//width = height = 10.0f + 5.0f * gens;

	//if (g != nullptr && gens >= 1) {
	//	for (int i = 0; i < 2; i++) {
	//		if (numOfAsteroids_ < ASTEROIDS_MAX_NUMBER) {
	//			int r = sdlutils().rand().nextInt(0, 360);
	//			Vector2D pos = at->getPos() + at->getVel().rotate(r) * 2 * max(width, height);
	//			Vector2D vel = at->getVel() * 1.1f;
	//			(sdlutils().rand().nextInt(0, 10) < 3) ? createYellowAsteroid(pos, vel, width, height, gens) : createWhiteAsteroid(pos, vel, width, height, gens);
	//		}
	//	}
	//}

	// ESTO DEBERIA IR AL GameCtrlSystem
	//// Condicion de victoria
	//if (numOfAsteroids_ == 0) {
	//	// Pone al caza en el centro de la ventana con velocidad cero y rotación cero
	//	mngr->resetFighter();

	//	// Se le resetean las vidas
	//	mngr->resetLives();

	//	// Menu de victoria
	//	mngr->endGame("win");
	//}
}

// Crea un asteroide blanco con sus componentes
void AsteroidsSystem::createWhiteAsteroid(Vector2D pos, Vector2D vel, float width, float height, int g) {
	asteroid = new Entity(_grp_ASTEROIDS_WHITE);
	mngr_->addComponent<Transform>(asteroid, pos, vel, width, height, 0);
	mngr_->addComponent<Generations>(asteroid, g);
	//mngr_->addComponent<ShowAtOppositeSide>(asteroid);
	//mngr_->addComponent<FramedImage>(asteroid, &SDLUtils::instance()->images().at("WhiteAsteroid"), ASTEROID_WHITE_FRAME_WIDTH, ASTEROID_WHITE_FRAME_HEIGHT, ASTEROID_WHITE_NUMCOLS, ASTEROID_WHITE_NUMROWS);
	mngr_->addEntity(asteroid);
	numOfAsteroids_++;
}

// Crea un asteroide amarillo con sus componentes
void AsteroidsSystem::createYellowAsteroid(Vector2D pos, Vector2D vel, float width, float height, int g) {
	asteroid = new Entity(_grp_ASTEROIDS_YELLOW);
	mngr_->addComponent<Transform>(asteroid, pos, vel, width, height, 0);
	mngr_->addComponent<Generations>(asteroid, g);
	/*mngr_->addComponent<ShowAtOppositeSide>(asteroid);
	mngr_->addComponent<FramedImage>(asteroid, &SDLUtils::instance()->images().at("YellowAsteroid"), ASTEROID_GOLD_FRAME_WIDTH, ASTEROID_GOLD_FRAME_HEIGHT, ASTEROID_WHITE_NUMCOLS, ASTEROID_WHITE_NUMROWS);
	mngr_->addComponent<Follow>(asteroid, mngr->getFighter()->getComponent<Transform>(_TRANSFORM));
	mngr->addEntity(asteroid);
	numOfAsteroids_++;*/
}

// Devuelve una posicion aleatoria
//Vector2D AsteroidsSystem::choosePosition(float width, float height) {
//	Vector2D p;
//
//	// Elegimos su posición p de manera aleatoria en los bordes de la ventana
//	int b = sdlutils().rand().nextInt(0, 4);
//	switch (b) {
//	case 0: p = { WIN_WIDTH + width , (float)(sdlutils().rand().nextInt(0, WIN_HEIGHT)) }; break;
//	case 1: p = { (float)(sdlutils().rand().nextInt(0, WIN_WIDTH)) , -(height) }; break;
//	case 2: p = { (float)(sdlutils().rand().nextInt(0, WIN_WIDTH)) , WIN_HEIGHT + width }; break;
//	case 3: p = { -(width), (float)(sdlutils().rand().nextInt(0, WIN_HEIGHT)) }; break;
//	}
//
//	return p;
//}

//// Devuelve una velocidad aleatoria
//Vector2D AsteroidsSystem::chooseVelocity(Vector2D p) {
//	//Vector2D c = { WIN_HALF_WIDTH + (float)(sdlutils().rand().nextInt(-100, 101)), WIN_HALF_HEIGHT + (float)(sdlutils().rand().nextInt(-100, 101)) };
//	//float speed = (float)(sdlutils().rand().nextInt(1, 10) / 10.0f);
//	//return ((c - p).normalize() * speed);
//}

// Actualiza su vector de velocidad para perseguir al fighter
//void Follow::update() {
//	Vector2D v = transform->getVel();
//	Vector2D p = transform->getPos();
//	Vector2D q = followObjectTransform->getPos();
//	transform->setVel(transform->getVel().rotate(v.angle(q - p) > 0 ? 1.0f : -1.0f));
//}