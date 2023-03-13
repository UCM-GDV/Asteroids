#include "BulletSystem.h"

    // Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void BulletsSystem::receive(const Message& m) {
	switch (m.id) {
		case _m_FIGTHER_ASTEROID_COLLIDED: destroyAllBullets(); break;
		case _m_FIGHTER_SHOOT: shoot(m.fighter_shoot.pos, m.fighter_shoot.vel, m.fighter_shoot.width, m.fighter_shoot.height);
	}
}
    // Inicializar el sistema, etc.
void BulletsSystem::initSystem() {
	fighterGun = mngr_->getEntities(_grp_FIGHTER).at(0)->getComponent<Gun>(_GUN);
	assert(fighterGun != nullptr);
}

// Si el juego está parado no hacer nada, en otro caso mover las balas y
// desactivar las que salen de la ventana como en la práctica 1.
void BulletsSystem::update() {
	for (Entity* bullet : mngr_->getEntities(_grp_BULLETS)) {
		bullet->update();
	}

	//
}

// Para gestionar el mensaje de que el jugador ha disparado. Añadir una bala al
// juego, como en la práctica 1. Recuerda que la rotación de la bala sería
// vel.angle(Vector2D(0.0f,-1.0f))
void BulletsSystem::shoot(Vector2D pos, Vector2D vel, double width, double height) {

}

// Para gestionar el mensaje de que ha habido un choque entre una bala y un
// asteroide. Desactivar la bala “b”.
void BulletsSystem::onCollision_BulletAsteroid(Entity* b) {

}

// Destruye todas las balas de la escena
void BulletsSystem::destroyAllBullets() {
	for (auto& e : mngr_->getEntities(_grp_BULLETS)) {
		e->setAlive(false);
	}
}





// ESTO DE AQUI NO LO VAMOS A USAR PORQUE TENEMOS MAQUINA DE ESTADOS
// Para gestionar el mensaje de que ha acabado la ronda. Desactivar todas las
// balas, y desactivar el sistema.
void BulletsSystem::onRoundOver() {

}

// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
void BulletsSystem::onRoundStart() {

}

