/*Vector2D pos = transform->getPos()
			+ Vector2D(transform->getW() / 2.0f, transform->getH() / 2.0f)
			- Vector2D(0.0f, transform->getH() / 2.0f + 5.0f + 12.0f).rotate(transform->getR())
			- Vector2D(2.0f, 10.0f);*/

#pragma once
#include "../ecs/Entity.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/bulletComponents/DisableOnExit.h"
#include "../entities/fighter.h"

class Bullet : public Entity {
private:
	Transform* transform;

public:
	// Constructora
	Bullet(Fighter* fighter);
	// Destructora
	~Bullet();
};