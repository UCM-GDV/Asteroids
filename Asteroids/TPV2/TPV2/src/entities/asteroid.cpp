#include "asteroid.h"

Asteroid::Asteroid(Game* _game) : Entity() {

	// TRANSFORM COMPONENT
	addComponent<Transform>((int)(_TRANSFORM), Vector2D(WIN_WIDTH / 2, WIN_HEIGHT / 2), Vector2D(0,0), ASTEROID_WIDTH_1, ASTEROID_HEIGHT_1, 0);
	// IMAGE COMPONENT
	addComponent<FramedImage>((int)(_FRAMEDIMAGE), &SDLUtils::instance()->images().at("WhiteAsteroid"));
}

Asteroid::~Asteroid() {}