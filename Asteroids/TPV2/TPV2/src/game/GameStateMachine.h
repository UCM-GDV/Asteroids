#pragma once
#ifndef GAME_STATE_MACHINE_H_
#define GAME_STATE_MACHINE_H_
#include <stack>
#include "../ecs/Manager.h"
#include "../utils/Singleton.h"
using namespace std;

class GameStateMachine : public Singleton<GameStateMachine> {
    friend Singleton<GameStateMachine>;
private:
    stack<Manager*> gameStates;
    stack<Manager*> gameStatesToErase;
public:
    // Constructora
    GameStateMachine();
    // Destructora
    ~GameStateMachine();
    // Anade un estado a la pila
    void pushState(Manager* newState);
    // Borra el estado de la cima de la pila
    void popState();
    // Borra todos los estados de la pila
    void clearStates();
    // Devuelve el estado actual
    Manager* currentState();
    // Borra la pila y anade un nuevo estado
    void changeState(Manager* newState);
    // Borra los punteros de los estados a borrar
    void clearStatesToErase();
};
#endif