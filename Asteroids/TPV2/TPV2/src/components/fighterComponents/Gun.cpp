#pragma once
#include "Gun.h"
#include "../../states/PlayState.h"
Gun::Gun() : transform(nullptr), startTime(SDL_GetTicks()) {}

Gun::~Gun() {
	transform = nullptr;
}

void Gun::initComponent() {
	transform = ent_->getComponent<Transform>(_TRANSFORM);
	assert(transform != nullptr);
	//playState = static_cast<PlayState*>(mngr_);
	//assert(playState != nullptr);
}

void Gun::handleEvent(SDL_Event event) {
	if (InputHandler::instance()->keyDownEvent()) {
		if (InputHandler::instance()->isKeyDown(SDLK_s)) {
			int frameTime = SDL_GetTicks() - startTime;
			if (frameTime >= 250) {
				tryShoot();
				SDLUtils::instance()->soundEffects().at("fire").play();
				startTime = SDL_GetTicks();
			}
		}
	}
}

void Gun::tryShoot() {
	//mngr_->addEntity(new Bullet();
	static_cast<PlayState*>(mngr_)->addBullet();
}

		
