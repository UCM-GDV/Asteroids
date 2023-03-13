#include "RenderSystem.h"
#include "../states/EndState.h"
#include "../states/PauseState.h"
#include "../states/PlayState.h"

// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void RenderSystem::receive(const Message& m) {
	//switch (m.id) {
	//	case algo: algo2; break;
	// default; break;
	//}
}

// Inicializar el sistema, etc.
void RenderSystem::initSystem() {
	fighterTransform = mngr_->getEntities(_grp_FIGHTER).at(0)->getComponent<Transform>(_TRANSFORM);
	assert(fighterTransform != nullptr);
	fighterHealth = mngr_->getEntities(_grp_FIGHTER).at(0)->getComponent<Health>(_HEALTH);
	assert(fighterHealth != nullptr);
}

// - Dibujar asteroides, balas y caza (sólo si el juego no está parado).
// - Dibujar las vidas (siempre).
// - Dibujar los mensajes correspondientes: si el juego está parado, etc (como en
// la práctica 1)
void RenderSystem::update() {
	// Caza
	SDL_Rect dest = build_sdlrect(fighterTransform->getPos(), fighterTransform->getW(), fighterTransform->getH());
	SDLUtils::instance()->images().at("Fighter").render(dest, fighterTransform->getR());

	// Vidas
	for (int i = 0; i < fighterHealth->getLives(); ++i) {
		SDL_Rect dest;
		dest.x = i * LIVES_WIDTH + LIVES_POSITION.getX();
		dest.y = LIVES_POSITION.getY();
		dest.w = LIVES_WIDTH;
		dest.h = LIVES_HEIGHT;
		SDLUtils::instance()->images().at("Fighter").render(dest);
	}
	
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
	else if (static_cast<PauseState*>(mngr_) != nullptr || static_cast<EndState*>(mngr_) != nullptr) {
		for (Entity* msg :mngr_->getEntities(_grp_MESSAGES)) {
			msg->render();
		}
	}
}

//// ESTO DE AQUI NO LO VAMOS A USAR PORQUE TENEMOS MAQUINA DE ESTADOS
//// Para gestionar los mensajes correspondientes y actualizar los atributos
//// winner_ y state_. 
//void RenderSystem::onRoundStart() {
//	//if (static_cast<PlayState*>(mngr_) != nullptr) {
//	//	
//	//}
//	//else if (static_cast<PauseState*>(mngr_) != nullptr || static_cast<EndState*>(mngr_) != nullptr) {
//	//	
//	//}
//}
//void RenderSystem:: onRoundOver() {}
//void RenderSystem::onGameStart() {}
//void RenderSystem:: onGameOver() {}
