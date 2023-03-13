#include "GameCtrlSystem.h"

    // Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
void GameCtrlSystem::receive(const Message& m) {}
    // Inicializar el sistema, etc.
void GameCtrlSystem::initSystem() {}
    // Si el juego no est� parado y el jugador pulsa SDLK_SPACE cambia el estado
    // como en la pr�ctica 1, etc. Tiene que enviar mensajes correspondientes cuando
    // empieza una ronda o cuando empieza una nueva partida.
void GameCtrlSystem::update() {}
    // Para gestionar el mensaje de que ha habido un choque entre el fighter y un
    // un asteroide. Tiene que avisar que ha acabado la ronda, quitar una vida
    // al fighter, y si no hay m�s vidas avisar que ha acabado el juego (y quien
    // es el ganador).
void GameCtrlSystem::onCollision_FighterAsteroid() {}
    // Para gestionar el mensaje de que no hay m�s asteroides. Tiene que avisar que
    // ha acabado la ronda y adem�s que ha acabado el juego (y quien es el ganador)
void GameCtrlSystem::onAsteroidsExtinction() {}
