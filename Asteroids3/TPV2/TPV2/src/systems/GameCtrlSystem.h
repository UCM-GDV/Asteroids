#pragma once
#include "../ecs/System.h"
#include "../sdlutils/InputHandler.h"
#include "../systems/FighterSystem.h"
#include "../components/Callback.h"

//Mantiene el estado del juego, o se comunica con la máquina de estados para transitar entre 
//ellos. Decide cuándo acaba una ronda, cuando acaba el juego, etc.
class GameCtrlSystem : public System {
private:
	// Estado actual del juego
	int state; 
    // Resultado del ganador
    int winner;
    // Puntero a las vidas del fighter
    Health* fighterHealth;
    Health* fighterHealth1;
    Health* fighterHealth2;

    // Para gestionar el mensaje de que ha habido un choque entre el fighter y un
    // un asteroide. Tiene que avisar que ha acabado la ronda, quitar una vida
    // al fighter, y si no hay más vidas avisar que ha acabado el juego (y quien
    // es el ganador).
    void onCollision_FighterAsteroid();
    // Para gestionar el mensaje de que no hay más asteroides. Tiene que avisar que
    // ha acabado la ronda y además que ha acabado el juego (y quien es el ganador)
    void onAsteroidsExtinction();
    // Si hay colision entre fighter y bullet en el modo multijugador
    // Gestiona las vidas y si alguno llega a 0, se coloca el endState
    void onCollision_FighterBullet(int fighterHealth);

    // UI
    string name;
    string nameWithSpaces;
    string ip;
    string ipWithSpaces;
    // Devuelve si el cursor esta encima de un boton o no
    bool isOver(Entity* button, std::pair<Sint32, Sint32>) const;
    void addCharacter();
    void addSpaces(string text, string& textWithSpaces);
    void addNumberOrDot();

public:
    // Identificador
    constexpr static sysId_type id = _sys_GAMECTRL;

    // Constructoras
    GameCtrlSystem();
    GameCtrlSystem(int state_);
    // Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
    void receive(const Message& m) override;
    // Inicializar el sistema, etc.
    void initSystem() override;
    // Si el juego no está parado y el jugador pulsa SDLK_SPACE cambia el estado
    // como en la práctica 1, etc. Tiene que enviar mensajes correspondientes cuando
    // empieza una ronda o cuando empieza una nueva partida.
    virtual void update() override;

    inline string getIp() { return ipWithSpaces; }
    inline string getname() { return name; }
    void onChangeState();
};