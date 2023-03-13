#include "RenderSystem.h"
#include "../states/EndState.h"
#include "../states/PauseState.h"
#include "../states/PlayState.h"

// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
void RenderSystem::receive(const Message& m) {

}

// Inicializar el sistema, etc.
void RenderSystem::initSystem() {

}

// - Dibujar asteroides, balas y caza (s�lo si el juego no est� parado).
// - Dibujar las vidas (siempre).
// - Dibujar los mensajes correspondientes: si el juego est� parado, etc (como en
// la pr�ctica 1)
void RenderSystem::update() {
	// Caza + Vidas
	for (Entity* fighter : mngr_->getEntities(_grp_FIGHTER)) {
		fighter->render();
	}

	// Si el juego no esta parado
	if (static_cast<PlayState*>(mngr_) != nullptr) {
		// Asteroides
		for (Entity* ast : mngr_->getEntities(_grp_ASTEROIDS)) {
			ast->render();
		}

		// Balas
		for (Entity* bullet : mngr_->getEntities(_grp_BULLETS)) {
			bullet->render();
		}
	}
	// Mensajes en el resto de estados (PauseState y EndState)
	else {
		for (Entity* msg :mngr_->getEntities(_grp_MESSAGES)) {
			msg->render();
		}
	}
}

// Para gestionar los mensajes correspondientes y actualizar los atributos
// winner_ y state_. 
void RenderSystem::onRoundStart() {

}
void RenderSystem:: onRoundOver() {

}
void RenderSystem::onGameStart() {

}
void RenderSystem:: onGameOver() {

}
