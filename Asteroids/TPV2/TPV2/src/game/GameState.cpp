#include "GameState.h"
#include "../game/Game.h"

// Constructora
GameState::GameState(Game* _game) : game(_game) {}

// Destructora
GameState::~GameState() {
    /*for (Manager* manager : sceneManagers) {
        delete(manager);
    }*/
}

// Actualiza los objetos de la escena
void GameState::update() {
    /*for (Manager* manager : sceneManagers) {
        manager->update();
    }

    refresh();*/
}

// Dibuja la escena en pantalla
void GameState::render() const {
    /*for (Manager* manager : sceneManagers) {
        manager->render();
    }*/
}

// Maneja el evento actual
void GameState::handleEvent(SDL_Event event) {
    /*for (Manager* manager : sceneManagers) {
        manager->handleEvent(event);
    }*/
}

// Borra todos los GameObject no vivos
void GameState::refresh() {
    for (Manager* manager : sceneManagers) {
        manager->refresh();
    }
}