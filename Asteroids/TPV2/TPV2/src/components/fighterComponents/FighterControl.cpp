#pragma once
#include "FighterControl.h"

FighterControl::FighterControl() : transform(nullptr) {}

FighterControl::~FighterControl() {
	transform = nullptr;
}

void FighterControl::initComponent() {
	transform = ent_->getComponent<Transform>(_TRANSFORM);
	assert(transform != nullptr);
	&SDLUtils::instance()->soundEffects().at("thrust");
}

void FighterControl::rotate(float r_) {
	transform->changeRot(degreesToRadians(r_));
}

void FighterControl::acelerate() {
	// reproducir sonido
	
	Vector2D newVel = transform->getVel() +Vector2D(0.0f, -1.0f).rotate(transform->getR()) * 0.7f;
	if (newVel.getY() <= SPEED_LIMIT.getY()) transform->setVel(newVel);
}

float FighterControl::degreesToRadians(float degrees_) {
	return (degrees_ * (M_PI / 180));
}