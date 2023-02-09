#pragma once
#ifndef GAME_STATE_H_
#define GAME_STATE_H_
#include <list>
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
class Game;
using namespace std;

class GameState {
protected:
    Game* game = nullptr;
    list<Manager*> sceneManagers;
public:
    // Constructora
    GameState(Game* _game);
    // Destructora
    virtual ~GameState();
    // Actualiza los objetos de la escena
    virtual void update();
    // Dibuja la escena en pantalla
    virtual void render() const;
    // Maneja el evento actual
    virtual void handleEvent(SDL_Event event);
    // Borra todos los GameObject no vivos
    void refresh();
};
#endif
