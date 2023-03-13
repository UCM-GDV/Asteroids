#include "GameCtrlSystem.h"

    // Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void GameCtrlSystem::receive(const Message& m) {}
    // Inicializar el sistema, etc.
void GameCtrlSystem::initSystem() {}
    // Si el juego no está parado y el jugador pulsa SDLK_SPACE cambia el estado
    // como en la práctica 1, etc. Tiene que enviar mensajes correspondientes cuando
    // empieza una ronda o cuando empieza una nueva partida.
void GameCtrlSystem::update() {}
    // Para gestionar el mensaje de que ha habido un choque entre el fighter y un
    // un asteroide. Tiene que avisar que ha acabado la ronda, quitar una vida
    // al fighter, y si no hay más vidas avisar que ha acabado el juego (y quien
    // es el ganador).
void GameCtrlSystem::onCollision_FighterAsteroid() {}
    // Para gestionar el mensaje de que no hay más asteroides. Tiene que avisar que
    // ha acabado la ronda y además que ha acabado el juego (y quien es el ganador)
void GameCtrlSystem::onAsteroidsExtinction() {}
