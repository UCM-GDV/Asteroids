#include "GameStateMachine.h"

// Constructora
GameStateMachine::GameStateMachine() {}

// Destructora
GameStateMachine::~GameStateMachine() {
    clearStates();
    clearStatesToErase();
}

// Anade un estado a la pila
void GameStateMachine::pushState(GameState* newState) { gameStates.push(newState); }

// Borra el estado de la cima de la pila
void GameStateMachine::popState() {
    gameStatesToErase.push(gameStates.top());
    gameStates.pop();
}

// Borra todos los estados de la pila
void GameStateMachine::clearStates() {
    while (!gameStates.empty()) popState();
}

// Devuelve el estado actual
GameState* GameStateMachine::currentState() { return gameStates.top(); }

// Borra la pila y anade un nuevo estado
void GameStateMachine::changeState(GameState* newState) {
    clearStates();
    pushState(newState);
}

// Borra los punteros de los estados a borrar
void GameStateMachine::clearStatesToErase() {
    while (!gameStatesToErase.empty()) {
        delete(gameStatesToErase.top());
        gameStatesToErase.pop();
    }
}