#include "BulletSystem.h"

    // Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void BulletSystem::receive(const Message& m) {
	switch (m.id) {
		case _m_FIGTHER_ASTEROID_COLLIDED: destroyAllBullets(); break;
		case _m_FIGHTER_SHOOT: shoot(m.fighter_shoot.pos, m.fighter_shoot.vel, m.fighter_shoot.width, m.fighter_shoot.height);
	}
}
    // Inicializar el sistema, etc.
void BulletSystem::initSystem() {
	/*fighterGun = mngr_->getEntities(_grp_FIGHTER).at(0)->getComponent<Gun>(_GUN);
	assert(fighterGun != nullptr);*/
}

// Si el juego está parado no hacer nada, en otro caso mover las balas y
// desactivar las que salen de la ventana como en la práctica 1.
void BulletSystem::update() {
	for (Entity* bullet : mngr_->getEntities(_grp_BULLETS)) {
		//bullet->update();
		//if (transform->getPos().getX() < -(BULLET_WIDTH) || transform->getPos().getX() > (WIN_WIDTH + BULLET_WIDTH) || transform->getPos().getY() < -(BULLET_HEIGHT) || transform->getPos().getY() > (WIN_HEIGHT + BULLET_HEIGHT)) {
		//		ent_->setAlive(false);
		//}
	}

	//
}

// Para gestionar el mensaje de que el jugador ha disparado. Añadir una bala al
// juego, como en la práctica 1. Recuerda que la rotación de la bala sería
// vel.angle(Vector2D(0.0f,-1.0f))
void BulletSystem::shoot(Vector2D pos, Vector2D vel, double width, double height) {
		/*Vector2D bPos, bVel;
		bPos = fighterTransform->getPos()
			+ Vector2D(FIGHTER_HALF_WIDTH, FIGHTER_HALF_HEIGHT)
			- Vector2D(0.0f, FIGHTER_HEIGHT / 2.0f + 5.0f + 12.0f).rotate(fighterTransform->getR())
			- Vector2D(2.0f, 10.0f);
		bVel = Vector2D(0.0f, -1.0f).rotate(fighterTransform->getR()) * (fighterTransform->getVel().magnitude() + 5.0f);

		bullet = new Entity();
		bullet->addComponent<Transform>(_TRANSFORM, bPos, bVel, BULLET_WIDTH, BULLET_HEIGHT, fighterTransform->getR());
		bullet->addComponent<Image>(_IMAGE, &SDLUtils::instance()->images().at("Bullet"));
		bullet->addComponent<DisableOnExit>(_DISABLEONEXIT);
		addEntity(bullet, _grp_BULLETS);*/
	
}

// Para gestionar el mensaje de que ha habido un choque entre una bala y un
// asteroide. Desactivar la bala “b”.
void BulletSystem::onCollision_BulletAsteroid(Entity* b) {

}

// Destruye todas las balas de la escena
void BulletSystem::destroyAllBullets() {
	for (auto& e : mngr_->getEntities(_grp_BULLETS)) {
		e->setAlive(false);
	}
}





// ESTO DE AQUI NO LO VAMOS A USAR PORQUE TENEMOS MAQUINA DE ESTADOS
// Para gestionar el mensaje de que ha acabado la ronda. Desactivar todas las
// balas, y desactivar el sistema.
//void BulletSystem::onRoundOver() {

//}

//// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
//void BulletSystem::onRoundStart() {

//}

