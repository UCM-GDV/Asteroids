#pragma once
#include "Gun.h"
#include "../../states/PlayState.h"

// Constructora
Gun::Gun() : transform(nullptr), startTime(SDL_GetTicks()) {}

// Destructora
Gun::~Gun() {
	transform = nullptr;
}

// Inicializa el componente
void Gun::initComponent() {
	assert(transform != nullptr);
}

// Recoge el input del jugador
void Gun::handleEvent(SDL_Event event) {
	if (InputHandler::instance()->keyDownEvent()) {
		if (InputHandler::instance()->isKeyDown(SDLK_s)) {
			int frameTime = SDL_GetTicks() - startTime;
			if (frameTime >= 250) {
				//tryShoot();
				SDLUtils::instance()->soundEffects().at("fire").play();
				startTime = SDL_GetTicks();
			}
		}
	}
}
//
//// Confirma que se trata de la escena de PlayState y anade una bala a la escena
//void Gun::tryShoot() {
//	static_cast<PlayState*>(mngr_)->addBullet();
//}

		
