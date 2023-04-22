#include "../states/PlayState.h"
#include "CollisionsSystem.h"
#include "../ecs/Manager.h"

// Constructora
CollisionsSystem::CollisionsSystem(int state_) : state(state_) {}

// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void CollisionsSystem::receive(const Message& m) {}

// Inicializar el sistema, etc.
void CollisionsSystem::initSystem() {
	fighterTransform = mngr_->getSystem<FighterSystem>()->getFighterTransform();
	assert(fighterTransform != nullptr);
}

// Si el juego está parado no hacer nada, en otro caso comprobar colisiones como
// en la práctica 1 y enviar mensajes correspondientes.
void CollisionsSystem::update() {
	// Si esta en PlayState
	if (state == 1){
		collision(mngr_->getEntities(_grp_ASTEROIDS_WHITE));
		collision(mngr_->getEntities(_grp_ASTEROIDS_YELLOW));
	}
	if (state == 3) { //colision el grupo de balas con algun fighter y luego fighter fighter

		collisionNet(mngr_->getEntities(_grp_BULLETS));
	}
}
void  CollisionsSystem::collisionNet(vector<Entity*> v) {
	int i = 0; bool end = false;
	Transform* f1 = mngr_->getSystem<FighterSystem>()->getFighterTransform1();
	Transform* f2 = mngr_->getSystem<FighterSystem>()->getFighterTransform2();
	while (i < v.size() && !end) {
		Transform* bulletTransform = mngr_->getComponent<Transform>(v[i]);
		if (collisionEntities(bulletTransform, f1)) {
			//MANDAR MENSAJE COLISION F1 Y BALA
			//DESTRUIR BALA, QUITAR VIDA y RESETEAR 
			cout << "bala-f1" << endl;

		}
		else if (collisionEntities(bulletTransform, f2)) {
			//MANDAR MENSAJE COLISION F2 Y BALA
			//DESTRUIR BALA, QUITAR VIDA RESETEAR
			cout << "bala-f2" << endl;

		}
	}
	if (collisionEntities(f2, f1)) {
		//MANDAR MENSAJE COLISION ENTRE DOS FIGHTERS
		//RESTAR VIDA A LOS DOS Y RESETEAR
		cout << "f2-f1" << endl;

	}
}
// Detecta las colisiones dependendiendo del grupo de asteroide
void CollisionsSystem::collision(vector<Entity*> v) {
	int i = 0; bool end = false;
	while (i < v.size() && !end) {
		Transform* asteroidTransform = mngr_->getComponent<Transform>(v[i]);
		if (collisionEntities(asteroidTransform, fighterTransform)) {
			Message m;
			m.id = _m_FIGTHER_ASTEROID_COLLIDED;
			mngr_->send(m);
			end = true;
		}
		else {
			for (auto& bullet : mngr_->getEntities(_grp_BULLETS)) {
				if (collisionEntities(mngr_->getComponent<Transform>(bullet), asteroidTransform)) {
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

// Devuelve si la bala ha colisionado con algun asteroide
bool CollisionsSystem::collisionEntities(Transform* Trans, Transform* Trans2) {
	return col->collidesWithRotation(Trans->getPos(), Trans->getW(), Trans->getH(), Trans->getR(),
		Trans2->getPos(), Trans2->getW(), Trans2->getH(), Trans2->getR());
}