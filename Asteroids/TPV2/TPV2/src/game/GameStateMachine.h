#pragma once
#ifndef GAME_STATE_MACHINE_H_
#define GAME_STATE_MACHINE_H_
#include <stack>
#include "GameState.h"
using namespace std;

class GameStateMachine {
private:
    stack<GameState*> gameStates;
    stack<GameState*> gameStatesToErase;
public:
    // Constructora
    GameStateMachine();
    // Destructora
    ~GameStateMachine();
    // Anade un estado a la pila
    void pushState(GameState* newState);
    // Borra el estado de la cima de la pila
    void popState();
    // Borra todos los estados de la pila
    void clearStates();
    // Devuelve el estado actual
    GameState* currentState();
    // Borra la pila y anade un nuevo estado
    void changeState(GameState* newState);
    // Borra los punteros de los estados a borrar
    void clearStatesToErase();
};
#endif