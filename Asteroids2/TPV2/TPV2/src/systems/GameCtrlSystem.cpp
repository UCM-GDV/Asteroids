#include "GameCtrlSystem.h"
#include "../ecs/Manager.h"
#include "../game/GameStateMachine.h"
#include "../states/PauseState.h"
#include "../states/PlayState.h"
#include "../states/EndState.h"
#include "../game/Game.h"

// Constructora
GameCtrlSystem::GameCtrlSystem() : fighterHealth(nullptr) {}
GameCtrlSystem::GameCtrlSystem(int state_) : state(state_), fighterHealth(nullptr) {}

// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void GameCtrlSystem::receive(const Message& m) {
    switch (m.id) {
        // colision asteroide con fighter
    case _m_FIGTHER_ASTEROID_COLLIDED: onCollision_FighterAsteroid(); break;
    case _m_ASTEROIDS_EXTINCTION: onAsteroidsExtinction(); break;
    default: break;
    }
}

// Inicializar el sistema, etc.
void GameCtrlSystem::initSystem() {
    fighterHealth = mngr_->getSystem<FighterSystem>()->getFighterHealth();
    assert(fighterHealth != nullptr);
}

// Si el juego no está parado y el jugador pulsa SDLK_SPACE cambia el estado
// como en la práctica 1, etc.
//  Tiene que enviar mensajes correspondientes cuando
// empieza una ronda o cuando empieza una nueva partida.
void GameCtrlSystem::update() {
   
    if (InputHandler::instance()->keyDownEvent()) {
		if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
			// Si esta en PlayState
			if (state == 1) {
				GameStateMachine::instance()->pushState(new PauseState());
			}
			// Si esta en PauseState
			else if (state == 0) {
				GameStateMachine::instance()->popState();
                Message m;
                m.id = _m_ROUND_STARTED;
                GameStateMachine::instance()->currentState()->send(m);
			}
			// Si esta en EndState
			else if (state == 2) {
				GameStateMachine::instance()->changeState(new PauseState());
			}
        }
    }
}

// Para gestionar el mensaje de que ha habido un choque entre el fighter y un
// un asteroide. Tiene que avisar que ha acabado la ronda, quitar una vida
// al fighter, y si no hay más vidas avisar que ha acabado el juego (y quien
// es el ganador).
void GameCtrlSystem::onCollision_FighterAsteroid() {
    
    fighterHealth->decreaseLives();
	Message m;
    if (fighterHealth->getlife() <= 0) {
		m.id = _m_ONDEFEAT;
        GameStateMachine::instance()->pushState(new EndState(2));
    }
    else {
		m.id = _m_ROUND_FINISHED;
        GameStateMachine::instance()->pushState(new PauseState());
    }
	mngr_->send(m);

   
}

// Para gestionar el mensaje de que no hay más asteroides. Tiene que avisar que
// ha acabado la ronda y además que ha acabado el juego (y quien es el ganador)
void GameCtrlSystem::onAsteroidsExtinction() {
    Message m;
    m.id = _m_ONVICTORY;
    mngr_->send(m);

    GameStateMachine::instance()->pushState(new EndState(1));
}
