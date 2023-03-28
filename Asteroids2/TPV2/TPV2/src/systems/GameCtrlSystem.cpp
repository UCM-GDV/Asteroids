#include "GameCtrlSystem.h"
#include "../ecs/Manager.h"
#include "../game/GameStateMachine.h"
#include "../states/PauseState.h"
#include "../states/PlayState.h"

// Constructora
GameCtrlSystem::GameCtrlSystem() : fighterHealth(nullptr) {}
GameCtrlSystem::GameCtrlSystem(int state_) : state(state_), fighterHealth(nullptr) {}

// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void GameCtrlSystem::receive(const Message& m) {
    switch (m.id) {
        //colision asteroide con fighter
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
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_SPACE) {
			    // Si esta en PlayState
			    if (state == 1) {
				    GameStateMachine::instance()->pushState(new PauseState());
			    }
			    // Si esta en PauseState
			    else if (state == 0) {
				    GameStateMachine::instance()->popState();
			    }
			    // Si esta en EndState
			    else if (state == 2) {
				    GameStateMachine::instance()->changeState(new PauseState());
			    }
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
    }
    else {
		m.id = _m_ROUND_FINISHED;
    }
	mngr_->send(m);

    //GameStateMachine::instance()->pushState(new PauseState());
}

// Para gestionar el mensaje de que no hay más asteroides. Tiene que avisar que
// ha acabado la ronda y además que ha acabado el juego (y quien es el ganador)
void GameCtrlSystem::onAsteroidsExtinction() {
    Message m;
    m.id = _m_ONVICTORY;
    mngr_->send(m);

    // añadir el endstate dependiendo de las vidas
    //GameStateMachine::instance()->pushState(new EndState("win")); //Uint8 winner_; // 0 - None, 1 - Asteroids, 2- Fighter
}
