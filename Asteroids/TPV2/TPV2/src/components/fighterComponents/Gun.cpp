#pragma once
#include "Gun.h"

Gun::Gun() : transform(nullptr) {}

Gun::~Gun() {
	transform = nullptr;
}

void Gun::initComponent() {
	transform = ent_->getComponent<Transform>(_TRANSFORM);
	assert(transform != nullptr);
}

void Gun::tryShoot() {
	//new Bullet(transform->get)
	static_cast<PlayState*>(mngr_)->;
}

