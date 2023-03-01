#pragma once
#include <cassert>
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "../utils/Singleton.h"
class PlayState;
class Entity;

class AsteroidsManager: public Singleton<AsteroidsManager> {

	friend Singleton<AsteroidsManager>; 
private:
	int numasteroids;
	int startTime;
	PlayState* mngr;
	Entity* asteroid;
public:
	// Constructora
	AsteroidsManager();
	void init(PlayState* m);
	// Destructora
	virtual ~AsteroidsManager();
	// Crea n asteroides
	void createAsteroids(int n);
	// Reutiliza el metodo de createAsteroids para instanciar 1 asteroide cada cierto tiempo
	void addAsteroidFrequently();
	// Destruye todos los asteroides pertenecientes al _grp_ASTEROIDS de las entidades de la escena
	void destroyAllAsteroids();
	// Cuando exista una colision con un asteroide, se generan 2 mas dependiendo de su numGen 
	// y teniendo en cuenta el numero de asteroides en escena
	void onCollision(Entity* a);
};