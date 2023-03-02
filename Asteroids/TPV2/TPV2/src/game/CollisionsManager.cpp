#include "CollisionsManager.h"
#include "../states/PlayState.h"

// Constructora
CollisionsManager::CollisionsManager() {}

// Destructora
CollisionsManager::~CollisionsManager() {
	col = nullptr;
	mngr = nullptr;
	fighterTransform = nullptr;
}

// Inicializa
void CollisionsManager::init(PlayState* m) {
	mngr = m;
	fighterTransform = mngr->getFighter()->getComponent<Transform>(_TRANSFORM);	
}

// Comprueba las colisiones de todos los asteroides con el fighter y las balas
void CollisionsManager::checkCollision() {
	vector<Entity*> v = mngr->getEntities(_grp_ASTEROIDS);
	int i = 0; bool end = false;
	while(i < v.size() && !end) {
		Transform* asteroidTransform = v[i]->getComponent<Transform>(_TRANSFORM);
		if (fighterCollision(asteroidTransform)) {
			AsteroidsManager::instance()->destroyAllAsteroids();
			destroyAllBullets();
			fighterOnCollision();
			AsteroidsManager::instance()->createAsteroids(ASTEROIDS_INITIAL_NUMBER);
			end = true;
		}
		else {
			for (auto& bullet : mngr->getEntities(_grp_BULLETS)) {
				if (bulletCollision(bullet->getComponent<Transform>(_TRANSFORM), asteroidTransform)) {
					// Desactiva la bala
					bullet->setAlive(false);
					AsteroidsManager::instance()->onCollision(v[i]);
				}
			}
		}
		++i;
	}
}

// Destruye todas las balas de la escena
void CollisionsManager::destroyAllBullets() {
	for (auto& e : mngr->getEntities(_grp_BULLETS)) {
		e->setAlive(false);
	}
}

// Devuelve si algun asteroide ha colisionado con el fighter
bool CollisionsManager::fighterCollision(Transform* asteroidTransform) {
	return col->collidesWithRotation(asteroidTransform->getPos(), asteroidTransform->getW(), asteroidTransform->getH(), asteroidTransform->getR(),
		fighterTransform->getPos(), fighterTransform->getW(), fighterTransform->getH(), fighterTransform->getR());
}

// Devuelve si la bala ha colisionado con algun asteroide
bool CollisionsManager::bulletCollision(Transform* bulletTransform, Transform* asteroidTransform) {
	return col->collidesWithRotation(bulletTransform->getPos(), bulletTransform->getW(), bulletTransform->getH(), bulletTransform->getR(),
		asteroidTransform->getPos(), asteroidTransform->getW(), asteroidTransform->getH(), asteroidTransform->getR());
}

// Quita una vida, resetea y gestiona si se pausa o se finaliza el juego
void CollisionsManager::fighterOnCollision() {
	// Le quita una vida al fighter
	Health* fighterHealthComponent = mngr->getFighter()->getComponent<Health>(_HEALTH);
	fighterHealthComponent->decreaseLive();

	// Pausa o finaliza el juego
	(fighterHealthComponent->getLives() <= 0) ? mngr->endGame("lose") : mngr->pauseGame();

	// Sonido de explosion del fighter
	sdlutils().soundEffects().at("explosion").play();

	// Pone al caza en el centro de la ventana con velocidad cero y rotación cero
	resetFighter();
}

// Reestablece la posicion, velocidad y rotacion del fighter
void CollisionsManager::resetFighter() {
	fighterTransform->setPos({ WIN_HALF_WIDTH, WIN_HALF_HEIGHT });
	fighterTransform->setVel(FIGHTER_VELOCITY);
	fighterTransform->setRot(0);
}