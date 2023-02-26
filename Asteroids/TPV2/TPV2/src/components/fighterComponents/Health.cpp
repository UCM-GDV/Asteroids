#include "Health.h"

void Health::initComponent() {
	texture = &SDLUtils::instance()->images().at("Life");
}

void Health::render() {
	for (int i = 0; i < lives; ++i) {
		SDL_Rect dest;
		dest.x = i * LIVES_WIDTH + LIVES_POSITION.getX();
		dest.y = LIVES_POSITION.getY();
		dest.w = LIVES_WIDTH;
		dest.h = LIVES_HEIGHT;
		texture->render(dest);
	}
}

int Health::getLives() {
	return lives;
}

void Health::setLives(int lives_) {
	lives = lives_;
}

void Health::resetLives() {
	lives = NUMBER_LIVES;
}