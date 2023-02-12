#pragma once
#ifndef ASTEROID_H_
#define ASTEROID_H_
#include "../ecs/Entity.h"
#include "../game/Game.h"
#include "../game/ecs_def.h"
#include "../components/asteroidsComponents/FramedImage.h"
#include "../sdlutils/SDLUtils.h"

class Asteroid : public Entity {
	public:
		// Constructora
		Asteroid(Game* _game);
		// Destructora
		~Asteroid();
};
#endif // !ASTEROID_H_
