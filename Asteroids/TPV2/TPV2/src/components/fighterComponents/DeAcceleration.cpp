#include "DeAcceleration.h"
#include <iostream>
DeAcceleration::DeAcceleration() : transform(nullptr) {}

void DeAcceleration::initComponent() {
	transform = ent_->getComponent<Transform>(_TRANSFORM);
	if (transform == nullptr) {
		throw "No tiene transform el fighter";
	}
}

void DeAcceleration::update() {
	Vector2D vel = transform->getVel();
	if (vel.getY() < 0.05f) transform->setVel(Vector2D(0,0));
	else transform->setVel(vel * 0.995f);
}