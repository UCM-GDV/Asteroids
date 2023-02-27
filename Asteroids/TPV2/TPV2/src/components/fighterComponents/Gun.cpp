#pragma once
#include "Gun.h"
#include "../../states/PlayState.h"
Gun::Gun() : transform(nullptr) {}

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
			tryShoot();
		}
	}
}

void Gun::tryShoot() {
	//mngr_->addEntity(new Bullet();
	static_cast<PlayState*>(mngr_)->addBullet();
}

		
