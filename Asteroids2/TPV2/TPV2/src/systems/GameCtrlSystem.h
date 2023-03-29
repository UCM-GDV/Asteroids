#pragma once
#include "../ecs/System.h"
#include "../sdlutils/InputHandler.h"
#include "../systems/FighterSystem.h"

//Mantiene el estado del juego, o se comunica con la m�quina de estados para transitar entre 
//ellos. Decide cu�ndo acaba una ronda, cuando acaba el juego, etc.
class GameCtrlSystem : public System {
public:
    // Identificador
    constexpr static sysId_type id = _sys_GAMECTRL;

    // Constructoras
    GameCtrlSystem();
    GameCtrlSystem(int state_);
    // Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
    void receive(const Message& m) override;
    // Inicializar el sistema, etc.
    void initSystem() override;
    // Si el juego no est� parado y el jugador pulsa SDLK_SPACE cambia el estado
    // como en la pr�ctica 1, etc. Tiene que enviar mensajes correspondientes cuando
    // empieza una ronda o cuando empieza una nueva partida.
    virtual void update() override;
private:
	// Estado actual del juego
	int state; 
    // Puntero a las vidas del fighter
    Health* fighterHealth;

    // Para gestionar el mensaje de que ha habido un choque entre el fighter y un
    // un asteroide. Tiene que avisar que ha acabado la ronda, quitar una vida
    // al fighter, y si no hay m�s vidas avisar que ha acabado el juego (y quien
    // es el ganador).
    void onCollision_FighterAsteroid();
    // Para gestionar el mensaje de que no hay m�s asteroides. Tiene que avisar que
    // ha acabado la ronda y adem�s que ha acabado el juego (y quien es el ganador)
    void onAsteroidsExtinction();
};