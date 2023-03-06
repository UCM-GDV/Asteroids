#include "Health.h"

// Constructora
Health::Health() : texture(nullptr), lives(NUMBER_LIVES) {}

// Destructora
Health::~Health() {
	texture = nullptr;
}

// Inicializa el componente
void Health::initComponent() {
	texture = &SDLUtils::instance()->images().at("Life");
}

// Renderiza el numero de vidas actual
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