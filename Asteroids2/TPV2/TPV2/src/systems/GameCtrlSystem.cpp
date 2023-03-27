#include "GameCtrlSystem.h"

// Constructora
GameCtrlSystem::GameCtrlSystem() : fighterHealth(nullptr) {}
GameCtrlSystem::GameCtrlSystem(int state_) : state(state_), fighterHealth(nullptr) {}

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
    fighterHealth = mngr_->getSystem<FighterSystem>()->getFighterHealth();
    assert(fighterHealth != nullptr);
}

// Si el juego no está parado y el jugador pulsa SDLK_SPACE cambia el estado
// como en la práctica 1, etc.
//  Tiene que enviar mensajes correspondientes cuando
// empieza una ronda o cuando empieza una nueva partida.
void GameCtrlSystem::update() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        InputHandler::instance()->update(event);
        if (InputHandler::instance()->keyDownEvent()) {
            if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
                // Si esta en PlayState
                if (state == 1) {
                    Message m;
                    m.id = _m_UPDATE_POSITION;
                    //mngr_->send(m);
                     // Si pulsa SDLK_SPACE cambia de estado al de PauseState
                    // Condicion de victoria y de derrota desde mensajes de otros systems AQUI???
                } 
                // Si esta en PauseState
                else if (state == 0) {
                    // Si pulsa SDLK_SPACE cambia de estado al de PlayState
                    
                }
                // Si esta en EndState
                else if (state == 2) {
                   // Si pulsa SDLK_SPACE cambia de estado al de PauseState
                   
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
    // anadir el pausestate
}

// Para gestionar el mensaje de que no hay más asteroides. Tiene que avisar que
// ha acabado la ronda y además que ha acabado el juego (y quien es el ganador)
void GameCtrlSystem::onAsteroidsExtinction() {
   // añadir el endstate dependiendo de las vidas
    //Uint8 winner_; // 0 - None, 1 - Asteroids, 2- Fighter
}
