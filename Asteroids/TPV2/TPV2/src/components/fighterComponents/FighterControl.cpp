#pragma once
#include "FighterControl.h"
// Constructora
FighterControl::FighterControl() : transform(nullptr) {}
// Destructora
FighterControl::~FighterControl() {
	transform = nullptr;
}
// Inicializa el componente
void FighterControl::initComponent() {
	transform = ent_->getComponent<Transform>(_TRANSFORM);
	assert(transform != nullptr);
}
// Rota el transofrm del fighter
void FighterControl::rotate(float r_) {
	transform->changeRot(degreesToRadians(r_));
}
// Recoge el input del jugador
void FighterControl::handleEvent(SDL_Event event) {
	InputHandler::instance()->update(event);

	if (InputHandler::instance()->keyDownEvent()) {
		if (InputHandler::instance()->isKeyDown(SDLK_LEFT)) {
			rotate(-(FIGHTER_ROTATION_SPEED));
		}
		else if (InputHandler::instance()->isKeyDown(SDLK_RIGHT)) {
			rotate(FIGHTER_ROTATION_SPEED);
		}
		else if (InputHandler::instance()->isKeyDown(SDLK_UP)) {
			acelerate();
			sdlutils().soundEffects().at("thrust").play();
		}
	}
}
// Acelera al fighter
void FighterControl::acelerate() {
	// reproducir sonido
	
	Vector2D newVel = transform->getVel() +Vector2D(0.0f, -1.0f).rotate(transform->getR()) * 0.7f;
	if (newVel.getY() <= SPEED_LIMIT.getY()) transform->setVel(newVel);
}
// Convierte los grados a radianes
float FighterControl::degreesToRadians(float degrees_) {
	return (degrees_ * (M_PI / 180));
}