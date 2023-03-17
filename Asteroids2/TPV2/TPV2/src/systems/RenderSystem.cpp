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
	/*fighterTransform = mngr_->getEntities(_grp_FIGHTER).at(0)->getComponent<Transform>(_TRANSFORM);
	assert(fighterTransform != nullptr);
	fighterHealth = mngr_->getEntities(_grp_FIGHTER).at(0)->getComponent<Health>(_HEALTH);
	assert(fighterHealth != nullptr);*/
}

// - Dibujar asteroides, balas y caza (sólo si el juego no está parado).
// - Dibujar las vidas (siempre).
// - Dibujar los mensajes correspondientes: si el juego está parado, etc (como en
// la práctica 1)
void RenderSystem::update() {
	//SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 30, 50, 0);
	//SDL_RenderClear(sdlutils().renderer());

	//// Caza
	//SDL_Rect dest = build_sdlrect(fighterTransform->getPos(), fighterTransform->getW(), fighterTransform->getH());
	//SDLUtils::instance()->images().at("Fighter").render(dest, fighterTransform->getR());

	//// Vidas
	//for (int i = 0; i < fighterHealth->getLives(); ++i) {
	//	Vector2D healthPosition = Vector2D(i * LIVES_WIDTH + LIVES_POSITION.getX(), LIVES_POSITION.getY());
	//	SDL_Rect dest = build_sdlrect(healthPosition, LIVES_WIDTH, LIVES_HEIGHT);
	//	SDLUtils::instance()->images().at("Fighter").render(dest);
	//}

	//// Si el juego no esta parado
	//if (static_cast<PlayState*>(mngr_) != nullptr) {
	//	// Asteroides
	//	for (Entity* ast : mngr_->getEntities(_grp_ASTEROIDS)) {
	//		// Update
	//		//currentframe = (currentframe + 1) % (numCols * numRows - 1);
	//		//    currentTime = 0;
	//		// Render
	//		// text_ = SDLUtils::instance()->images().at()
	//		//SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
	//		//    SDL_Rect src;
	//		//    src.x = (currentframe % numCols) * fw;
	//		//    src.y = (currentframe / numCols) * fh;
	//		//    src.w = fw;
	//		//    src.h = fh;
	//		//    tex_->render(src, dest);
	//	}

	//	// Balas
	//	for (Entity* bullet : mngr_->getEntities(_grp_BULLETS)) {
	//		bullet->render();
	//	}
	//}
	//// Mensajes en el resto de estados (PauseState y EndState)
	//else if (static_cast<PauseState*>(mngr_) != nullptr || static_cast<EndState*>(mngr_) != nullptr) {
	//	for (Entity* msg :mngr_->getEntities(_grp_MESSAGES)) {
	//		msg->render();
	//	}
	//}

	//SDL_RenderPresent(sdlutils().renderer());
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
