//#pragma once
//#include <cassert>
//#include "../sdlutils/SDLUtils.h"
//#include "../utils/Vector2D.h"
//#include "../utils/Singleton.h"
//class PlayState;
//class Entity;
//
//class AsteroidsManager: public Singleton<AsteroidsManager> {
//	friend Singleton<AsteroidsManager>; 
//private:
//	int numasteroids;
//	int startTime;
//	
//	PlayState* mngr;
//	Entity* asteroid;
//public:
//	// Constructora
//	AsteroidsManager();
//	// Destructora
//	virtual ~AsteroidsManager();
//	// Inicializa
//	void init(PlayState* m);	
//	// Crea n asteroides
//	void createAsteroids(int n);
//	// Reutiliza el metodo de createAsteroids para instanciar 1 asteroide cada cierto tiempo
//	void addAsteroidFrequently();
//	// Destruye todos los asteroides pertenecientes al _grp_ASTEROIDS de las entidades de la escena
//	void destroyAllAsteroids();
//	// Cuando exista una colision con un asteroide, se generan 2 mas dependiendo de su numGen 
//	// y teniendo en cuenta el numero de asteroides en escena
//	void onCollision(Entity* a);
//	// Crea un asteroide blanco con sus componentes
//	void createWhiteAsteroid(Vector2D pos, Vector2D vel, float width, float height, int g);
//	// Crea un asteroide amarillo con sus componentes
//	void createYellowAsteroid(Vector2D pos, Vector2D vel, float width, float height, int g);
//	// Devuelve una posicion aleatoria
//	Vector2D choosePosition(float width, float height);
//	// Devuelve una velocidad aleatoria
//	Vector2D chooseVelocity(Vector2D p);
//};