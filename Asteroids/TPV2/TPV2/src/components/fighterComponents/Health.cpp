#include "Health.h"

void Health::initComponent() {
	texture = &SDLUtils::instance()->images().at("Life");
}

void Health::render() {
	for (int i = 0; i < lives; ++i) {
		SDL_Rect dest;
		dest.x = i * 46;
		dest.y = 160;
		dest.w = 46;
		dest.h = 46;
		texture->render(dest);
	}
}