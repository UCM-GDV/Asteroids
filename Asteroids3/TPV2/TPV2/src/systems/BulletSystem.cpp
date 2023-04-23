#include "BulletSystem.h"
#include "../ecs/Manager.h"
#include "NetWorkSystem.h"

// Constructora
BulletSystem::BulletSystem(int state_) : state(state_) {}

// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void BulletSystem::receive(const Message& m) {
	switch (m.id) {
		case _m_ROUND_FINISHED: case _m_ONDEFEAT: case _m_ONVICTORY: case _m_FIGHTER_BULLET_COLLIDED: destroyAllBullets(); break;
		case _m_FIGHTER_SHOOT: shoot(m.fighter_shoot.pos, m.fighter_shoot.vel, m.fighter_shoot.width, m.fighter_shoot.height, m.fighter_shoot.rot); break;
		case _m_BULLET_ASTEROID_COLLIDED: onCollision_BulletAsteroid(m.bullet_asteroid_coll.bullet); break;
		case _m_NET_ADD_BULLET: addBullet(m.add_bullet.pos, m.add_bullet.vel, m.add_bullet.rot); break;
		default: break;
	}
}

// Inicializar el sistema, etc.
void BulletSystem::initSystem() {}

// Si el juego está parado no hacer nada, en otro caso mover las balas y
// desactivar las que salen de la ventana como en la práctica 1.
void BulletSystem::update() {
	for (Entity* bullet : mngr_->getEntities(_grp_BULLETS)) {
		auto tr = mngr_->getComponent<Transform>(bullet);
		tr->position_ = tr->position_ + tr->velocity_;
		// DISABLEONEXIT
		if (tr->getPos().getX() < -(BULLET_WIDTH) || tr->getPos().getX() > (WIN_WIDTH + BULLET_WIDTH) || tr->getPos().getY() < -(BULLET_HEIGHT) || tr->getPos().getY() > (WIN_HEIGHT + BULLET_HEIGHT)) {
				bullet->setAlive(false);
		}
	}
}

// Para gestionar el mensaje de que el jugador ha disparado. Añadir una bala al
// juego, como en la práctica 1. Recuerda que la rotación de la bala sería
// vel.angle(Vector2D(0.0f,-1.0f))
void BulletSystem::shoot(Vector2D pos, Vector2D vel, double width, double height, float rot) {
	Vector2D bPos, bVel;
	bPos = pos
		+ Vector2D(width / 2, height / 2)
		- Vector2D(0.0f, height / 2.0f + 5.0f + 12.0f).rotate(rot)
		- Vector2D(2.0f, 10.0f);
	bVel = Vector2D(0.0f, -1.0f).rotate(rot) * (vel.magnitude() + 5.0f);

	addBullet(bPos, bVel, rot);

	// Si esta en el estado de PlayStateMultiplayer, 
	// debe contactar con el otro para que se anada
	// una bala en su escena
	if (state == 3) {
		Message m;
		m.id = _m_ADD_BULLET;
		m.add_bullet.pos = bPos;
		m.add_bullet.vel = bVel;
		m.add_bullet.rot = rot;
		mngr_->send(m);
	}
}

// Para gestionar el mensaje de que ha habido un choque entre una bala y un
// asteroide. Desactivar la bala “b”.
void BulletSystem::onCollision_BulletAsteroid(Entity* b) {
	b->setAlive(false);
}

// Destruye todas las balas de la escena
void BulletSystem::destroyAllBullets() {
	for (auto& e : mngr_->getEntities(_grp_BULLETS)) {
		e->setAlive(false);
	}
}

// Para gestionar el mensaje de que ha acabado la ronda. Desactivar todas las
// balas, y desactivar el sistema.
void BulletSystem::onRoundOver() {
	// Desactiva todas las balas
	destroyAllBullets();
}

// Anade una bala a la escena
void BulletSystem::addBullet(Vector2D pos, Vector2D vel, float rot) {
	// Sonido
	SDLUtils::instance()->soundEffects().at("fire").play();

	Entity* bullet = new Entity(_grp_BULLETS);
	mngr_->addComponent<Transform>(bullet, pos, vel, BULLET_WIDTH, BULLET_HEIGHT, rot);
	mngr_->addEntity(bullet, _grp_BULLETS);
}
