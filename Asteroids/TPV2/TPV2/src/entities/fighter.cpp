#include "fighter.h"

Fighter::Fighter(Game* _game) : Entity() {

	// TRANSFORM COMPONENT
	addComponent<Transform>((int)(_TRANSFORM), Vector2D(WIN_WIDTH / 2, WIN_HEIGHT / 2), FIGHTER_VELOCITY, FIGHTER_WIDTH, FIGHTER_HEIGHT, FIGHTER_ROTATION);
	// IMAGE COMPONENT
	addComponent<Image>((int)(_IMAGE), &SDLUtils::instance()->images().at("Fighter"));
}

Fighter::~Fighter() {}