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
    state_ = 0;
    //COGER CCOMPONENTE DE VIDA
}

// Si el juego no está parado y el jugador pulsa SDLK_SPACE cambia el estado
// como en la práctica 1, etc.
// 
// 
//  Tiene que enviar mensajes correspondientes cuando
// empieza una ronda o cuando empieza una nueva partida.
void GameCtrlSystem::update() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        InputHandler::instance()->update(event);
        if (InputHandler::instance()->keyDownEvent()) {
            if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
                //si esta jugando
                if (state_ == 1) {
                    Message m;
                    m.id = _m_UPDATE_POSITION;
                    //mngr_->send(m);
                    // Condicion de victoria y de derrota desde mensajes de otros systems AQUI???
                }//si está parado
                else if (state_ == 0) {
                    // Si pulsa SDLK_SPACE cambia de estado al de PlayState
                    state_ = 1;
                   
                }//si es el final
                else if (state_ == 2) {
                   // Si pulsa SDLK_SPACE cambia de estado al de PauseState
                    state_ = 0;
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
  //AVISAR CAMBIO DE RONDA
  //COMPROBAR LAS VIDAS
//if(getlives()==0){
//     fin de juego
    state_=2; //fin de juego
    winner_=1;
    //}
    //
}

// Para gestionar el mensaje de que no hay más asteroides. Tiene que avisar que
// ha acabado la ronda y además que ha acabado el juego (y quien es el ganador)
void GameCtrlSystem::onAsteroidsExtinction() {
    //fin de ronda
    //fin de juego
    state_ = 2; //fin de juego
    winner_=2;
}
