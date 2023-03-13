#include "FighterSystem.h"
// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void FighterSystem::receive(const Message& m) {
    switch (m.id) {
        case _m_FIGTHER_ASTEROID_COLLIDED: onCollision_FighterAsteroid(); break;
        default: break;
    }
}
// Crear la entidad del caza, añadir sus componentes, asociarla con un handler
// correspondiente, etc.
void FighterSystem::initSystem() {
    fighterTransform = mngr_->getEntities(_grp_FIGHTER).at(0)->getComponent<Transform>(_TRANSFORM);
	assert(fighterTransform != nullptr);
}

// Si el juego está parado no hacer nada, en otro caso actualizar la velocidad
// del caza y moverlo como en la práctica 1 (acelerar, desacelerar, etc). Además, 
// si el juego no está parado y el jugador pulsa la tecla de disparo, enviar un
// mensaje con las características físicas de la bala. Recuerda que se puede disparar
// sólo una bala cada 0.25sec.
void FighterSystem::update() {
	
}

// Para reaccionar al mensaje de que ha habido un choque entre el fighter y un
// un asteroide. Poner el caza en el centro con velocidad (0,0) y rotación 0. No
// hace falta desactivar la entidad (no dibujarla si el juego está parado).
void FighterSystem::onCollision_FighterAsteroid() {
    resetFighter();

    //
}



//// Recoge el input del jugador
//void FighterControl::handleEvent(SDL_Event event) {
//	InputHandler::instance()->update(event);

//	if (InputHandler::instance()->keyDownEvent()) {
//		if (InputHandler::instance()->isKeyDown(SDLK_LEFT)) {
//			rotate(-(FIGHTER_ROTATION_SPEED));
//		}
//		else if (InputHandler::instance()->isKeyDown(SDLK_RIGHT)) {
//			rotate(FIGHTER_ROTATION_SPEED);
//		}
//		else if (InputHandler::instance()->isKeyDown(SDLK_UP)) {
//			acelerate();
//			sdlutils().soundEffects().at("thrust").play();
//		}
//	}
//}
// Acelera al fighter
void FighterSystem::accelerate() {
    Vector2D newVel = fighterTransform->getVel() + Vector2D(0.0f, -1.0f).rotate(fighterTransform->getR()) * 0.7f;
    if (newVel.getY() <= SPEED_LIMIT.getY()) fighterTransform->setVel(newVel);
}

// Rota el transofrm del fighter
void FighterSystem::rotate(float r_) {
	fighterTransform->changeRot(degreesToRadians(r_));
}
float  FighterSystem::degreesToRadians(float degrees_) {
	return (degrees_ * (M_PI / 180));
}


// ESTO DE AQUI NO LO VAMOS A USAR PORQUE TENEMOS MAQUINA DE ESTADOS
// Para gestionar el mensaje de que ha acabado una ronda. Desactivar el sistema.
void FighterSystem::onRoundOver() {
    // Desactiva el sistema
    active_ = false;
}

// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
void FighterSystem::onRoundStart() {
    // Activa el sistema
    active_ = true;
}
