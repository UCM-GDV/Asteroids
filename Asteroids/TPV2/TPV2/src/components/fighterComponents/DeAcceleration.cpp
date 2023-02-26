#include "DeAcceleration.h"

DeAcceleration::DeAcceleration() : transform(nullptr) {}

void DeAcceleration::initComponent() {
	transform = ent_->getComponent<Transform>(_TRANSFORM);
	assert(transform != nullptr);
}

void DeAcceleration::update() {
	Vector2D vel = transform->getVel();
	if (abs(vel.getY()) < 0.05f) transform->setVel(Vector2D(0,0));
	else transform->setVel(vel * 0.995f);
}