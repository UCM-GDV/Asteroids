#include "../states/PlayState.h"
#include "CollisionsSystem.h"
#include "../ecs/Manager.h"

// Constructora
CollisionsSystem::CollisionsSystem(int state_) : state(state_) {}

// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
void CollisionsSystem::receive(const Message& m) {}

// Inicializar el sistema, etc.
void CollisionsSystem::initSystem() {
	fighterTransform = mngr_->getSystem<FighterSystem>()->getFighterTransform();
	assert(fighterTransform != nullptr);
}

// Si el juego est� parado no hacer nada, en otro caso comprobar colisiones como
// en la pr�ctica 1 y enviar mensajes correspondientes.
void CollisionsSystem::update() {
	// Si esta en PlayState
	if (state == 1){
		collision(mngr_->getEntities(_grp_ASTEROIDS_WHITE));
		collision(mngr_->getEntities(_grp_ASTEROIDS_YELLOW));
	}
}

// Detecta las colisiones dependendiendo del grupo de asteroide
void CollisionsSystem::collision(vector<Entity*> v) {
	int i = 0; bool end = false;
	while (i < v.size() && !end) {
		Transform* asteroidTransform = mngr_->getComponent<Transform>(v[i]);
		if (fighterCollision(asteroidTransform)) {
			Message m;
			m.id = _m_FIGTHER_ASTEROID_COLLIDED;
			mngr_->send(m);
			end = true;
		}
		else {
			for (auto& bullet : mngr_->getEntities(_grp_BULLETS)) {
				if (bulletCollision(mngr_->getComponent<Transform>(bullet), asteroidTransform)) {
					Message m;
					m.id = _m_BULLET_ASTEROID_COLLIDED;
					m.bullet_asteroid_coll.asteroid = v[i];
					m.bullet_asteroid_coll.bullet = bullet;
					mngr_->send(m);
				}
			}
		}
		++i;
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