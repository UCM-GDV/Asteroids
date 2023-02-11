#include "fighter.h"

Fighter::Fighter(Game* _game) : Entity() {
	
	Texture* texture = new Texture(_game->getRenderer(), "resources/images/fighter.png");

	cmpId_type transform = int(_TRANSFORM);

	addComponent<Transform>(transform, Vector2D(100, 100), Vector2D(0,0), 50, 50, 0);
	
	cmpId_type image = int(_IMAGE);

	addComponent<Image>(image, texture);
}

Fighter::~Fighter() {}