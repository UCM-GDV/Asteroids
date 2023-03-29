#include "FighterSystem.h"
#include "../ecs/Manager.h"

// Constructora
FighterSystem::FighterSystem(int state_) : state(state_) {}

// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
void FighterSystem::receive(const Message& m) {
    switch (m.id) {
        case _m_ROUND_FINISHED: onCollision_FighterAsteroid(); break;
		case _m_ONVICTORY: case _m_ONDEFEAT: onRoundOver(); break;
        default: break;
    }
}

// Crear la entidad del caza, a�adir sus componentes, asociarla con un handler
// correspondiente, etc.
void FighterSystem::initSystem() {
	startTime = SDL_GetTicks();
    // Anade el objeto fighter a la escena
    fighter = new Entity(_grp_FIGHTER);
    fighter->setContext(mngr_);
    fighterTransform = mngr_->addComponent<Transform>(fighter, Vector2D(WIN_HALF_WIDTH, WIN_HALF_HEIGHT), FIGHTER_VELOCITY, FIGHTER_WIDTH, FIGHTER_HEIGHT, FIGHTER_ROTATION);
    fighterTransform->setContext(fighter, mngr_);
    fighterHealth = mngr_->addComponent<Health>(fighter, NUMBER_LIVES);
	fighterHealth->setContext(fighter, mngr_);
    mngr_->addEntity(fighter, _grp_FIGHTER);
}

// Si el juego est� parado no hacer nada, en otro caso actualizar la velocidad
// del caza y moverlo como en la pr�ctica 1 (acelerar, desacelerar, etc). Adem�s, 
// si el juego no est� parado y el jugador pulsa la tecla de disparo, enviar un
// mensaje con las caracter�sticas f�sicas de la bala. Recuerda que se puede disparar
// s�lo una bala cada 0.25sec.
void FighterSystem::update() {
	// Si esta en PlayState
	if (state == 1) {
		SDL_Event event_;
		updatefighter();
		InputHandler::instance()->update(event_);
		if (InputHandler::instance()->keyDownEvent()) {
			if (InputHandler::instance()->isKeyDown(SDLK_s)) {
				// GUN
				int frameTime = SDL_GetTicks() - startTime;
				if (frameTime >= 250) {
					// Envia mensaje con las caracteristicas fisicas de la bala
					Message m;
					m.id = _m_FIGHTER_SHOOT;
					m.fighter_shoot.pos = fighterTransform->getPos();
					m.fighter_shoot.vel = fighterTransform->getVel();
					m.fighter_shoot.width = fighterTransform->getW();
					m.fighter_shoot.height = fighterTransform->getH();
					mngr_->send(m);

					startTime = SDL_GetTicks();
				}
			}
			// FIGHTERCONTROL
			if (InputHandler::instance()->isKeyDown(SDLK_LEFT)) {
				rotate(-(FIGHTER_ROTATION_SPEED));
			}
			else if (InputHandler::instance()->isKeyDown(SDLK_RIGHT)) {
				rotate(FIGHTER_ROTATION_SPEED);
			}
			else if (InputHandler::instance()->isKeyDown(SDLK_UP)) {
				accelerate();
			}
		}
	}
}

// TRANSFORM - DEACCELERATION - SHOWATOPPOSITESIDE 
void  FighterSystem::updatefighter() {
	// TRANSFORM
	fighterTransform->setPos(fighterTransform->getPos() + fighterTransform->getVel());

	// DEACCELERATION
	Vector2D vel = fighterTransform->getVel();
	if (abs(vel.getY()) < 0.05f) fighterTransform->setVel(Vector2D(0, 0));
	else fighterTransform->setVel(vel * 0.995f);

	// SHOWATOPPOSITESIDE
	if (fighterTransform->getPos().getX() < -(FIGHTER_WIDTH)) {
		fighterTransform->setPos(Vector2D(WIN_WIDTH, fighterTransform->getPos().getY()));
	}
	else if (fighterTransform->getPos().getX() > (WIN_WIDTH + FIGHTER_WIDTH)) {
		fighterTransform->setPos(Vector2D(0, fighterTransform->getPos().getY()));
	}
	if (fighterTransform->getPos().getY() < -(FIGHTER_HEIGHT)) {
		fighterTransform->setPos(Vector2D(fighterTransform->getPos().getX(), WIN_HEIGHT));
	}
	else if (fighterTransform->getPos().getY() > (WIN_HEIGHT + FIGHTER_HEIGHT)) {
		fighterTransform->setPos(Vector2D(fighterTransform->getPos().getX(), 0));
	}
}

// Devuelve el transform del fighter
Transform* FighterSystem::getFighterTransform() { return fighterTransform; }

// Devuelve el health del fighter
Health* FighterSystem::getFighterHealth() { return fighterHealth; }

// Para reaccionar al mensaje de que ha habido un choque entre el fighter y un
// un asteroide. Poner el caza en el centro con velocidad (0,0) y rotaci�n 0. No
// hace falta desactivar la entidad (no dibujarla si el juego est� parado).
void FighterSystem::onCollision_FighterAsteroid() {
	resetFighter();
}

// Para gestionar el mensaje de que ha acabado una ronda. Desactivar el sistema.
void FighterSystem::onRoundOver() {
	resetFighter();
	resetLives();
}

// Acelera al fighter
void FighterSystem::accelerate() {
	Vector2D newVel = fighterTransform->getVel() + Vector2D(0.0f, -1.0f).rotate(fighterTransform->getR()) * 0.7f;
	if (newVel.getY() <= SPEED_LIMIT.getY()) fighterTransform->setVel(newVel);

	// Sonido
	sdlutils().soundEffects().at("thrust").play();
}

// Rota el transofrm del fighter
void FighterSystem::rotate(float r_) {
	fighterTransform->changeRot(degreesToRadians(r_));
}

