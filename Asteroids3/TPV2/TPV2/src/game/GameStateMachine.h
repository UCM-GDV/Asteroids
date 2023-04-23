#pragma once
#include <stack>
#include "../ecs/Manager.h"
#include "../utils/Singleton.h"
using namespace std;
class Game;

class GameStateMachine : public Singleton<GameStateMachine> {
    friend Singleton<GameStateMachine>;
private:
    Game* game;
    stack<Manager*> gameStates;
    stack<Manager*> gameStatesToErase;
public:
    // Constructora
    GameStateMachine();
    // Destructora
    ~GameStateMachine();
    // Inicializa la maquina
    void init(Game* game_);
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
    
    void quitGame();
    // Devuelve si esta la pila vacia o no
    inline bool isEmpty() { return gameStates.empty(); }
};