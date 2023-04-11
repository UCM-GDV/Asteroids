#include "BulletSystem.h"
#include "../ecs/Manager.h"

// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void BulletSystem::receive(const Message& m) {
	switch (m.id) {
		case _m_ROUND_FINISHED: case _m_ONDEFEAT: case _m_ONVICTORY: destroyAllBullets(); break;
		case _m_FIGHTER_SHOOT: shoot(m.fighter_shoot.pos, m.fighter_shoot.vel, m.fighter_shoot.width, m.fighter_shoot.height); break;
		case _m_BULLET_ASTEROID_COLLIDED: onCollision_BulletAsteroid(m.bullet_asteroid_coll.bullet); break;
		default: break;
	}
}

// Inicializar el sistema, etc.
void BulletSystem::initSystem() {
	fighterTransform = mngr_->getSystem<FighterSystem>()->getFighterTransform();
	assert(fighterTransform != nullptr);
}

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
void BulletSystem::shoot(Vector2D pos, Vector2D vel, double width, double height) {
	Vector2D bPos, bVel;
	bPos = fighterTransform->getPos()
		+ Vector2D(width/2, height/2)
		- Vector2D(0.0f, height / 2.0f + 5.0f + 12.0f).rotate(fighterTransform->getR())
		- Vector2D(2.0f, 10.0f);
	bVel = Vector2D(0.0f, -1.0f).rotate(fighterTransform->getR()) * (fighterTransform->getVel().magnitude() + 5.0f);

	Entity* bullet = new Entity(_grp_BULLETS);
	mngr_->addComponent<Transform>(bullet, bPos, bVel, BULLET_WIDTH, BULLET_HEIGHT, fighterTransform->getR());
	mngr_->addEntity(bullet, _grp_BULLETS);

	// Sonido
	SDLUtils::instance()->soundEffects().at("fire").play();
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

