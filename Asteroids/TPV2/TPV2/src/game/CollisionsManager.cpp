#include "CollisionsManager.h"
#include "../states/PlayState.h"

// Constructora
CollisionsManager::CollisionsManager() {}

// Inicializa
void CollisionsManager::init(PlayState* m) {
	mngr = m;
	fighterTransform = mngr->getFighter()->getComponent<Transform>(_TRANSFORM);	
}

// Comprueba las colisiones de todos los asteroides con el fighter y las balas
void CollisionsManager::checkCollision() {

	for (auto& e : mngr->getEntities(_grp_ASTEROIDS)) {
		Transform* eTransform = e->getComponent<Transform>(_TRANSFORM);
		
		bool collisionFighter = col->collidesWithRotation(eTransform->getPos(), eTransform->getW(), eTransform->getH(), eTransform->getR(),
			fighterTransform->getPos(), fighterTransform->getW(), fighterTransform->getH(), fighterTransform->getR());
		if (collisionFighter) {
			// Destruye todos los asteroides
			AsteroidsManager::instance()->destroyAllAsteroids();
			// Destruye todas las balas
			for (auto& e : mngr->getEntities(_grp_BULLETS)) {
				e->setAlive(false);
			}
			// Le quita una vida al fighter
			Health* fighterHealthComponent = mngr->getFighter()->getComponent<Health>(_HEALTH);
			fighterHealthComponent->decreaseLive();

			// marca el juego como PAUSED o GAMEOVER(depende de si
			//quedan vidas) 
			if (fighterHealthComponent->getLives() <= 0) {
				
			}
			// pon al caza en el centro de la ventana con velocidad cero y rotación cero
			resetFighter();
			break;
		}
		else {
			for (auto& a : mngr->getEntities(_grp_BULLETS)) {
				Transform* aTransform = a->getComponent<Transform>(_TRANSFORM);
				bool collisionBullet = col->collidesWithRotation(eTransform->getPos(), eTransform->getW(), eTransform->getH(), eTransform->getR(),
					aTransform->getPos(), aTransform->getW(), aTransform->getH(), aTransform->getR());
				if (collisionBullet) {
					//desactiva la bala
					//llama al on collision de asteroids le pasa e
					//si no hay mas asteroides el jugador gana
				}
			}
		}
	}
}

// Reestablece la posicion, velocidad y rotacion del fighter
void CollisionsManager::resetFighter() {
	fighterTransform->setPos({ WIN_HALF_WIDTH, WIN_HALF_HEIGHT });
	fighterTransform->setVel(FIGHTER_VELOCITY);
	fighterTransform->setRot(0);
}

// Destructora
CollisionsManager::~CollisionsManager() {
	col = nullptr;
	mngr = nullptr;
	fighterTransform = nullptr;
}
