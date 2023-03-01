#pragma once
#include <cassert>
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"

class PlayState;
class Entity;
class AsteroidsManager {
private:
	//siempre se inicia con 10 asteroides
	int numasteroids;
	int startTime;
	PlayState* mngr_;
	Entity* asteroid = nullptr;
public:
	AsteroidsManager(PlayState* m);
	virtual ~AsteroidsManager();
	void createAsteroids(int n);
	void addAsteroidFrequently();
	void destroyAllAsteroids();
	void onCollision(Entity* a);
};