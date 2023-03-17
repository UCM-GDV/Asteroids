#include "GameCtrlSystem.h"
#include "../states/EndState.h"
#include "../states/PauseState.h"
#include "../states/PlayState.h"

// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void GameCtrlSystem::receive(const Message& m) {
    switch (m.id) {
    case _m_FIGTHER_ASTEROID_COLLIDED: onCollision_FighterAsteroid(); break;
    case _m_ASTEROIDS_EXTINCTION: onAsteroidsExtinction(); break;
        default: break;
    }
}

// Inicializar el sistema, etc.
void GameCtrlSystem::initSystem() {
    winner_ = 0;
}

// Si el juego no está parado y el jugador pulsa SDLK_SPACE cambia el estado
// como en la práctica 1, etc. Tiene que enviar mensajes correspondientes cuando
// empieza una ronda o cuando empieza una nueva partida.
void GameCtrlSystem::update() {

    if (static_cast<PlayState*>(mngr_) != nullptr) {
        Message m;
        m.id = _m_UPDATE_POSITION;
        //mngr_->send(m);

        // Condicion de victoria y de derrota desde mensajes de otros systems
    }
    else if (static_cast<PauseState*>(mngr_) != nullptr) {
        // Si pulsa SDLK_SPACE cambia de estado al de PlayState
    }
    else if (static_cast<EndState*>(mngr_) != nullptr) {
        // Si pulsa SDLK_SPACE cambia de estado al de PauseState
    }
}

// Para gestionar el mensaje de que ha habido un choque entre el fighter y un
// un asteroide. Tiene que avisar que ha acabado la ronda, quitar una vida
// al fighter, y si no hay más vidas avisar que ha acabado el juego (y quien
// es el ganador).
void GameCtrlSystem::onCollision_FighterAsteroid() {

}

// Para gestionar el mensaje de que no hay más asteroides. Tiene que avisar que
// ha acabado la ronda y además que ha acabado el juego (y quien es el ganador)
void GameCtrlSystem::onAsteroidsExtinction() {

}
