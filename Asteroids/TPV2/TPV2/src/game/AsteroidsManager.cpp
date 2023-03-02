#include "AsteroidsManager.h"
#include "../states/PlayState.h"

// Constructora
AsteroidsManager::AsteroidsManager() : numasteroids(0), startTime(SDL_GetTicks()), asteroid(nullptr) {}

// Inicializa
void AsteroidsManager::init(PlayState* m) {
	mngr = m;
}

// Destructora
AsteroidsManager::~AsteroidsManager() {
	mngr = nullptr;
	asteroid = nullptr;
}

// Crea n asteroides
void AsteroidsManager::createAsteroids(int n) {
	for (int i = 0; i < n; i++) {
		if (numasteroids <= ASTEROIDS_MAX_NUMBER) {
			// Elige una generacion aleatoria entre 1 y 3
			int g = sdlutils().rand().nextInt(1, 4);
			float width, height;
			width = height = 10.0f + 5.0f * g;
			Vector2D p = choosePosition(width, height);
			Vector2D v = chooseVelocity(p);

			// Crea un tipo de asteroide dependiendo de una probabilidad
			(sdlutils().rand().nextInt(0, 10) < 3) ? createYellowAsteroid(p, v, width, height, g) : createWhiteAsteroid(p, v,width, height, g);
		}
	}

}

// Devuelve una posicion aletoria
Vector2D AsteroidsManager::choosePosition(float width, float height) {
	Vector2D p;

	// Elegimos su posición p de manera aleatoria en los bordes de la ventana
	int b = sdlutils().rand().nextInt(0, 4);
	switch (b) {
		case 0: p = { WIN_WIDTH + width , (float)(sdlutils().rand().nextInt(0, WIN_HEIGHT)) }; break;
		case 1: p = { (float)(sdlutils().rand().nextInt(0, WIN_WIDTH)) , -(height) }; break;
		case 2: p = { (float)(sdlutils().rand().nextInt(0, WIN_WIDTH)) , WIN_HEIGHT + width }; break;
		case 3: p = { -(width), (float)(sdlutils().rand().nextInt(0, WIN_HEIGHT)) }; break;
	}

	return p;
}

// Devuelve una velocidad aleatoria
Vector2D AsteroidsManager::chooseVelocity(Vector2D p) {
	Vector2D c = { WIN_HALF_WIDTH + (float)(sdlutils().rand().nextInt(-100, 101)), WIN_HALF_HEIGHT + (float)(sdlutils().rand().nextInt(-100, 101)) };
	float speed = (float)(sdlutils().rand().nextInt(1, 10) / 10.0f);
	return ((c - p).normalize() * speed);
}

// Crea un asteroide blanco con sus componentes
void AsteroidsManager::createWhiteAsteroid(Vector2D pos, Vector2D vel, float width, float height, int g) {
	asteroid = new Entity();
	asteroid->setContext(mngr);
	asteroid->addComponent<Transform>(_TRANSFORM, pos, vel, width, height, 0);
	asteroid->addComponent<Generations>(_GENERATIONS, g);
	asteroid->addComponent<ShowAtOppositeSide>(_SHOWATOPPOSIDESIDE);
	asteroid->addComponent<FramedImage>(_FRAMEDIMAGE, &SDLUtils::instance()->images().at("WhiteAsteroid"), ASTEROID_WHITE_FRAME_WIDTH, ASTEROID_WHITE_FRAME_HEIGHT, ASTEROID_WHITE_NUMCOLS, ASTEROID_WHITE_NUMROWS);
	mngr->addEntity(asteroid, _grp_ASTEROIDS);
	numasteroids++;
}

// Crea un asteroide amarillo con sus componentes
void AsteroidsManager::createYellowAsteroid(Vector2D pos, Vector2D vel, float width, float height, int g) {
	asteroid = new Entity();
	asteroid->setContext(mngr);
	asteroid->addComponent<Transform>(_TRANSFORM, pos, vel, width, height, 0);
	asteroid->addComponent<Generations>(_GENERATIONS, g);
	asteroid->addComponent<ShowAtOppositeSide>(_SHOWATOPPOSIDESIDE);
	asteroid->addComponent<FramedImage>(_FRAMEDIMAGE, &SDLUtils::instance()->images().at("YellowAsteroid"), ASTEROID_GOLD_FRAME_WIDTH, ASTEROID_GOLD_FRAME_HEIGHT, ASTEROID_WHITE_NUMCOLS, ASTEROID_WHITE_NUMROWS);
	asteroid->addComponent<Follow>(_FOLLOW, mngr->getFighter()->getComponent<Transform>(_TRANSFORM));
	mngr->addEntity(asteroid, _grp_ASTEROIDS);
	numasteroids++;
}

// Reutiliza el metodo de createAsteroids para instanciar 1 asteroide cada cierto tiempo
void AsteroidsManager::addAsteroidFrequently() {
	// Genera un asteroide nuevo cada 5 segundos 
	uint32_t frameTime = SDL_GetTicks() - startTime;
	if (frameTime >= ASTEROIDS_DELAY_TIME) {
		createAsteroids(1);
		startTime = SDL_GetTicks();
	}
}

// Destruye todos los asteroides pertenecientes al _grp_ASTEROIDS de las entidades de la escena
void AsteroidsManager::destroyAllAsteroids() {
	vector<Entity*> v = mngr->getEntities(_grp_ASTEROIDS);
	for (auto& ents : v) {
		ents->setAlive(false);
	}
	numasteroids = 0;
}

// Cuando exista una colision con un asteroide, se generan 2 mas dependiendo de su numGen 
// y teniendo en cuenta el numero de asteroides en escena
void AsteroidsManager::onCollision(Entity* a) {
	// Lo desactiva 
	a->setAlive(false);
	numasteroids--;
	Generations* g = a->getComponent<Generations>(_GENERATIONS);
	g->decreaseGeneration();
	Transform* at =  a->getComponent<Transform>(_TRANSFORM);

	int gens = g->getGenerations();
	float width, height;
	width = height = 10.0f + 5.0f * gens;

	if (g != nullptr && gens >= 1) {
		for (int i = 0; i < 2; i++) {
			if (numasteroids < ASTEROIDS_MAX_NUMBER) {
				int r = sdlutils().rand().nextInt(0, 360);
				Vector2D pos = at->getPos() + at->getVel().rotate(r) * 2 * max(width, height);
				Vector2D vel = at->getVel() * 1.1f;
				(sdlutils().rand().nextInt(0, 10) < 3) ? createYellowAsteroid(pos, vel, width, height, gens) : createWhiteAsteroid(pos, vel, width, height, gens);
			}
		}
	}

	// Condicion de victoria
	if (numasteroids == 0) {
		GameStateMachine::instance()->pushState(new EndState("win"));
	}
}
