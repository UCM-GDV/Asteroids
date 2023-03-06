#include "ShowAtOppositeSide.h"

// Constructora
ShowAtOppositeSide::ShowAtOppositeSide() : transform(nullptr) {}

// Destructora
ShowAtOppositeSide:: ~ShowAtOppositeSide() {
	transform = nullptr;
}

// Inicializa el componente
void ShowAtOppositeSide::initComponent() {
	transform = ent_->getComponent<Transform>(_TRANSFORM);
	assert(transform != nullptr);
}

// Actualiza el componente
void ShowAtOppositeSide::update() {
	if (transform->getPos().getX() < -(FIGHTER_WIDTH)) {
		transform->setPos(Vector2D(WIN_WIDTH, transform->getPos().getY()));
	}
	else if (transform->getPos().getX() > (WIN_WIDTH + FIGHTER_WIDTH)) {
		transform->setPos(Vector2D(0, transform->getPos().getY()));
	}
	if (transform->getPos().getY() < -(FIGHTER_HEIGHT) ) {
		transform->setPos(Vector2D(transform->getPos().getX(), WIN_HEIGHT));
	}
	else if (transform->getPos().getY() > (WIN_HEIGHT + FIGHTER_HEIGHT)) {
		transform->setPos(Vector2D(transform->getPos().getX(), 0));
	}
}
