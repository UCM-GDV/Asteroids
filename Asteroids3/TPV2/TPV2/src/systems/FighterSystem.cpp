#include "FighterSystem.h"
#include "../ecs/Manager.h"
#include "NetWorkSystem.h"

// Constructora
FighterSystem::FighterSystem(int state_) : state(state_) {}

// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void FighterSystem::receive(const Message& m) {
    switch (m.id) {
        case _m_ROUND_FINISHED: onCollision_FighterAsteroid(); break;
		case _m_ONVICTORY: case _m_ONDEFEAT: onRoundOver(); break;
		case _m_NET_FIGHTER_UPDATE: updateNet(m.fighterposup.pos, m.fighterposup.vel, m.fighterposup.width, m.fighterposup.height, m.fighterposup.rot);
        default: break;
    }
}

// Crear la entidad del caza, añadir sus componentes, asociarla con un handler
// correspondiente, etc.
void FighterSystem::initSystem() {
	startTime = SDL_GetTicks();
	if (state == 3) {
		// Anade el objeto fighter a la escena
		fighter1 = new Entity(_grp_FIGHTER);
		fighter1->setContext(mngr_);
		fighterTransform1 = mngr_->addComponent<Transform>(fighter1, FIGHTER_1_POS, FIGHTER_VELOCITY, FIGHTER_WIDTH, FIGHTER_HEIGHT, FIGHTER_1_ROTATION);
		fighterTransform1->setContext(fighter1, mngr_);
		fighterHealth1 = mngr_->addComponent<Health>(fighter1, NUMBER_LIVES);
		fighterHealth1->setContext(fighter1, mngr_);
		mngr_->addEntity(fighter1, _grp_FIGHTER);

		fighter2 = new Entity(_grp_FIGHTER);
		fighter2->setContext(mngr_);
		fighterTransform2 = mngr_->addComponent<Transform>(fighter2, FIGHTER_2_POS, FIGHTER_VELOCITY, FIGHTER_WIDTH, FIGHTER_HEIGHT, FIGHTER_2_ROTATION);
		fighterTransform2->setContext(fighter2, mngr_);
		fighterHealth2 = mngr_->addComponent<Health>(fighter2, NUMBER_LIVES);
		fighterHealth2->setContext(fighter2, mngr_);
		mngr_->addEntity(fighter2, _grp_FIGHTER);

		if (mngr_->getSystem<NetworkSystem>()->getServer()) {
			fighter = fighter1;
			fighterTransform = fighterTransform1;
			fighterHealth = fighterHealth1;
		}
		else {
			fighter = fighter2;
			fighterTransform = fighterTransform2;
			fighterHealth = fighterHealth2;
		}
	}
	else if (state == 0 || state == 1 || state == 2) {
		fighter = new Entity(_grp_FIGHTER);
		fighter->setContext(mngr_);
		fighterTransform = mngr_->addComponent<Transform>(fighter, FIGHTER_POS, FIGHTER_VELOCITY, FIGHTER_WIDTH, FIGHTER_HEIGHT, FIGHTER_ROTATION);
		fighterTransform->setContext(fighter, mngr_);
		fighterHealth = mngr_->addComponent<Health>(fighter, NUMBER_LIVES);
		fighterHealth->setContext(fighter, mngr_);
		mngr_->addEntity(fighter, _grp_FIGHTER);
	}
}

// Si el juego está parado no hacer nada, en otro caso actualizar la velocidad
// del caza y moverlo como en la práctica 1 (acelerar, desacelerar, etc). Además, 
// si el juego no está parado y el jugador pulsa la tecla de disparo, enviar un
// mensaje con las características físicas de la bala. Recuerda que se puede disparar
// sólo una bala cada 0.25sec.
void FighterSystem::move() {
	// Si esta en PlayState o en PlayStateMultiplayer
	SDL_Event event_;
	updateFighter();
	InputHandler::instance()->update(event_);
	if (InputHandler::instance()->keyDownEvent()) {
		if (InputHandler::instance()->isKeyDown(SDLK_s)) {
			// GUN
			int frameTime = SDL_GetTicks() - startTime;
			if (frameTime >= 250) {
				// Envia mensaje con las caracteristicas fisicas de la bala
				Message m;
				m.id = _m_FIGHTER_SHOOT;
				m.fighter_shoot.rot = fighterTransform->getR();
				m.fighter_shoot.pos = fighterTransform->getPos();
				m.fighter_shoot.vel = fighterTransform->getVel();
				m.fighter_shoot.width = fighterTransform->getW();
				m.fighter_shoot.height = fighterTransform->getH();
				mngr_->send(m);

				startTime = SDL_GetTicks();
			}
			m.id = _m_FIGHTER_UPDATE;
			m.fighter_update.rot = fighterTransform->getR();
			m.fighter_update.pos = fighterTransform->getPos();
			m.fighter_update.vel = fighterTransform->getVel();
			m.fighter_update.width = fighterTransform->getW();
			m.fighter_update.height = fighterTransform->getH();
			mngr_->send(m);
		}
		// FIGHTERCONTROL
		if (InputHandler::instance()->isKeyDown(SDLK_LEFT)) {
			rotate(-(FIGHTER_ROTATION_SPEED));
			m.id = _m_FIGHTER_UPDATE;
			m.fighter_update.rot = fighterTransform->getR();
			m.fighter_update.pos = fighterTransform->getPos();
			m.fighter_update.vel = fighterTransform->getVel();
			m.fighter_update.width = fighterTransform->getW();
			m.fighter_update.height = fighterTransform->getH();
			mngr_->send(m);
		}
		else if (InputHandler::instance()->isKeyDown(SDLK_RIGHT)) {
			rotate(FIGHTER_ROTATION_SPEED);
			m.id = _m_FIGHTER_UPDATE;
			m.fighter_update.rot = fighterTransform->getR();
			m.fighter_update.pos = fighterTransform->getPos();
			m.fighter_update.vel = fighterTransform->getVel();
			m.fighter_update.width = fighterTransform->getW();
			m.fighter_update.height = fighterTransform->getH();
			mngr_->send(m);
		}
		else if (InputHandler::instance()->isKeyDown(SDLK_UP)) {
			accelerate();
			m.id = _m_FIGHTER_UPDATE;
			m.fighter_update.rot = fighterTransform->getR();
			m.fighter_update.pos = fighterTransform->getPos();
			m.fighter_update.vel = fighterTransform->getVel();
			m.fighter_update.width = fighterTransform->getW();
			m.fighter_update.height = fighterTransform->getH();
			mngr_->send(m);
		}
	}

	
}

void FighterSystem::update() {
	switch (state) {
	case 1:
		move();

		break;

	case 3: 
		// Pregunta constantemente por el transform
		if (mngr_->getSystem<NetworkSystem>()->getServer()) {
			fighterTransform = fighterTransform1;
			fighterHealth = fighterHealth1;
		}
		else {
			fighterTransform = fighterTransform2;
			fighterHealth = fighterHealth2;
		}
		move();
		break;

	default: 
		break;
	}
	
}

// TRANSFORM - DEACCELERATION - SHOWATOPPOSITESIDE 
void FighterSystem::updateFighter() {
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

// Multiplayer
// Devuelve el transform del fighter 1
Transform* FighterSystem::getFighterTransform1() { return fighterTransform1; }
// Devuelve el transform del fighter 2
Transform* FighterSystem::getFighterTransform2() { return fighterTransform2; }
Transform* FighterSystem::setFighterTransform2() { return fighterTransform2; }
// Devuelve el health del fighter 1
Health* FighterSystem::getFighterHealth1() { return fighterHealth1; }
// Devuelve el health del fighter 2
Health* FighterSystem::getFighterHealth2() { return fighterHealth2; }

// Para reaccionar al mensaje de que ha habido un choque entre el fighter y un
// un asteroide. Poner el caza en el centro con velocidad (0,0) y rotación 0. No
// hace falta desactivar la entidad (no dibujarla si el juego está parado).
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

void FighterSystem::updateNet(Vector2D pos, Vector2D vel, double width, double height, float rot) {
	if (mngr_->getSystem<NetworkSystem>()->getServer()) {
		//si eres server actualizas client
		fighterTransform2->setPos(pos);
		fighterTransform2->setVel(vel);
		fighterTransform2->setW(width);
		fighterTransform2->setH(height);
		fighterTransform2->setRot(rot);
	}
	else {
		// si eres cliente actualizas server
		fighterTransform1->setPos(pos);
		fighterTransform1->setVel(vel);
		fighterTransform1->setW(width);
		fighterTransform1->setH(height);
		fighterTransform1->setRot(rot);
	}
}