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
    // FIGHTER
    fighter = new Entity(_grp_FIGHTER);
    fighter->setContext(mngr_);
    fighterTransform = mngr_->addComponent<Transform>(fighter, Vector2D(WIN_HALF_WIDTH, WIN_HALF_HEIGHT), FIGHTER_VELOCITY, FIGHTER_WIDTH, FIGHTER_HEIGHT, FIGHTER_ROTATION);
    fighterTransform->setContext(fighter, mngr_);
    fighterHealth = mngr_->addComponent<Health>(fighter);
	fighterHealth->setContext(fighter, mngr_);
	/*fighterShowAtOppositeSide = mngr_->addComponent<ShowAtOppositeSide>(fighter);
	fighterShowAtOppositeSide->setContext(fighter, mngr_);*/
    mngr_->addEntity(fighter, _grp_FIGHTER);

    // ASOCIARLA CON UN HANDLER
}

// Si el juego está parado no hacer nada, en otro caso actualizar la velocidad
// del caza y moverlo como en la práctica 1 (acelerar, desacelerar, etc). Además, 
// si el juego no está parado y el jugador pulsa la tecla de disparo, enviar un
// mensaje con las características físicas de la bala. Recuerda que se puede disparar
// sólo una bala cada 0.25sec.
void FighterSystem::update() {
	//Vector2D vel = transform->getVel();
	//if (abs(vel.getY()) < 0.05f) transform->setVel(Vector2D(0, 0));
	//else transform->setVel(vel * 0.995f);

	// SHOWATOPPOSITESIDE
	//if (transform->getPos().getX() < -(FIGHTER_WIDTH)) {
	//	transform->setPos(Vector2D(WIN_WIDTH, transform->getPos().getY()));
	//}
	//else if (transform->getPos().getX() > (WIN_WIDTH + FIGHTER_WIDTH)) {
	//	transform->setPos(Vector2D(0, transform->getPos().getY()));
	//}
	//if (transform->getPos().getY() < -(FIGHTER_HEIGHT)) {
	//	transform->setPos(Vector2D(transform->getPos().getX(), WIN_HEIGHT));
	//}
	//else if (transform->getPos().getY() > (WIN_HEIGHT + FIGHTER_HEIGHT)) {
	//	transform->setPos(Vector2D(transform->getPos().getX(), 0));
	//}
}

// Para reaccionar al mensaje de que ha habido un choque entre el fighter y un
// un asteroide. Poner el caza en el centro con velocidad (0,0) y rotación 0. No
// hace falta desactivar la entidad (no dibujarla si el juego está parado).
void FighterSystem::onCollision_FighterAsteroid() {
   // resetFighter();

    //
}



//// Recoge el input del jugador
//void FighterControl::handleEvent(SDL_Event event) {
//	InputHandler::instance()->update(event);
//    // FIGHTER CONTROL
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
//    // GUN
//if (InputHandler::instance()->keyDownEvent()) {
//	if (InputHandler::instance()->isKeyDown(SDLK_s)) {
//		int frameTime = SDL_GetTicks() - startTime;
//		if (frameTime >= 250) {
//			//tryShoot();
//			SDLUtils::instance()->soundEffects().at("fire").play();
//			startTime = SDL_GetTicks();
//		}
//	}
//}
//}

// Acelera al fighter
void FighterSystem::accelerate() {
  /*  Vector2D newVel = fighterTransform->getVel() + Vector2D(0.0f, -1.0f).rotate(fighterTransform->getR()) * 0.7f;
    if (newVel.getY() <= SPEED_LIMIT.getY()) fighterTransform->setVel(newVel);*/
}

// Rota el transofrm del fighter
void FighterSystem::rotate(float r_) {
	//fighterTransform->changeRot(degreesToRadians(r_));
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
