#include "CollisionsSystem.h"
#include "../states/PlayState.h"
	
// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void CollisionsSystem::receive(const Message& m) {
	/*switch (m.id) {
	case _m_ASTEROIDS_COLLISIONFIGHTER:
		
	break;
	default: break;
	}*/
}

// Inicializar el sistema, etc.
void CollisionsSystem::initSystem() {
	
}

// Si el juego está parado no hacer nada, en otro caso comprobar colisiones como
// en la práctica 1 y enviar mensajes correspondientes.

void CollisionsSystem::update() {
	if (static_cast<PlayState*>(mngr_)!= nullptr){

		vector<Entity*> v = mngr_->getEntities(_grp_ASTEROIDS);
		int i = 0; bool end = false;
		while (i < v.size() && !end) {
			Transform* asteroidTransform = v[i]->getComponent<Transform>(_TRANSFORM);
			if (fighterCollision(asteroidTransform)) {
				Message m;
				m.id = _m_FIGTHER_ASTEROID_COLLIDED;
				mngr_->send(m);
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
}

// Devuelve si algun asteroide ha colisionado con el fighter
bool CollisionsSystem::fighterCollision(Transform* asteroidTransform) {
	return col->collidesWithRotation(asteroidTransform->getPos(), asteroidTransform->getW(), asteroidTransform->getH(), asteroidTransform->getR(),
		fighterTransform->getPos(), fighterTransform->getW(), fighterTransform->getH(), fighterTransform->getR());
}

// Devuelve si la bala ha colisionado con algun asteroide
bool CollisionsSystem::bulletCollision(Transform* bulletTransform, Transform* asteroidTransform) {
	return col->collidesWithRotation(bulletTransform->getPos(), bulletTransform->getW(), bulletTransform->getH(), bulletTransform->getR(),
		asteroidTransform->getPos(), asteroidTransform->getW(), asteroidTransform->getH(), asteroidTransform->getR());
}

// ESTO DE AQUI NO LO VAMOS A USAR PORQUE TENEMOS MAQUINA DE ESTADOS
// Para gestionar el mensaje de que ha acabado una ronda. Desactivar el sistema.
void CollisionsSystem::onRoundOver() {

}

// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
void CollisionsSystem::onRoundStart() {

}


