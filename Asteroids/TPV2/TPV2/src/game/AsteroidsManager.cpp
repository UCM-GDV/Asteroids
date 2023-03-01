#include "AsteroidsManager.h"
#include "../states/PlayState.h"

// Constructora
AsteroidsManager::AsteroidsManager() : numasteroids(ASTEROIDS_INITIAL_NUMBER), startTime(SDL_GetTicks()), asteroid(nullptr) {}

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
			int g, b;
			float width, height, speed;
			Vector2D p, c;
			
			// Elige una generacion aleatoria entre 1 y 3
			g = sdlutils().rand().nextInt(1, 4);
			width = height = 10.0f + 5.0f * g;

			// Elegimos su posición p de manera aleatoria en los bordes de la ventana
			b = sdlutils().rand().nextInt(0, 4);
			switch (b) {
			case 0: p = { WIN_WIDTH + width , (float)(sdlutils().rand().nextInt(0, WIN_HEIGHT)) }; break;
			case 1: p = { (float)(sdlutils().rand().nextInt(0, WIN_WIDTH)) , -(height) }; break;
			case 2: p = { (float)(sdlutils().rand().nextInt(0, WIN_WIDTH)) , WIN_HEIGHT + width }; break;
			case 3: p = { -(width), (float)(sdlutils().rand().nextInt(0, WIN_HEIGHT)) }; break;
			}
			
			c = { WIN_HALF_WIDTH + (float)(sdlutils().rand().nextInt(-100, 101)), WIN_HALF_HEIGHT + (float)(sdlutils().rand().nextInt(-100, 101)) };
			speed = (float)(sdlutils().rand().nextInt(1, 10) / 10.0f);
			Vector2D v = (c - p).normalize() * speed;

			asteroid = new Entity();
			asteroid->setContext(mngr);
			asteroid->addComponent<Transform>(_TRANSFORM, p, v, width, height, 0);
			asteroid->addComponent<Generations>(_GENERATIONS, g);
			asteroid->addComponent<ShowAtOppositeSide>(_SHOWATOPPOSIDESIDE);
			//tipo b
			if (sdlutils().rand().nextInt(0, 10) < 3) {
				asteroid->addComponent<FramedImage>(_FRAMEDIMAGE, &SDLUtils::instance()->images().at("YellowAsteroid"), ASTEROID_GOLD_FRAME_WIDTH, ASTEROID_GOLD_FRAME_HEIGHT, ASTEROID_WHITE_NUMCOLS, ASTEROID_WHITE_NUMROWS);
				asteroid->addComponent<Follow>(_FOLLOW, mngr->getFighter()->getComponent<Transform>(_TRANSFORM));
			}
			//tipo a
			else {
				asteroid->addComponent<FramedImage>(_FRAMEDIMAGE, &SDLUtils::instance()->images().at("WhiteAsteroid"), ASTEROID_WHITE_FRAME_WIDTH, ASTEROID_WHITE_FRAME_HEIGHT, ASTEROID_WHITE_NUMCOLS, ASTEROID_WHITE_NUMROWS);
			}
			mngr->addEntity(asteroid, _grp_ASTEROIDS);
			numasteroids++;
		}
	}	
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
}

// Cuando exista una colision con un asteroide, se generan 2 mas dependiendo de su numGen 
// y teniendo en cuenta el numero de asteroides en escena
void AsteroidsManager::onCollision(Entity* a) {
	//lo desactiva 
	a->setAlive(false);
	
	Generations* g = a->getComponent<Generations>(_GENERATIONS);
	if (g != nullptr) {
		int gens = g->getGenerations();
		if (gens == 3 || gens == 2) {
			if (numasteroids < ASTEROIDS_MAX_NUMBER) {

			}
			//genera otros 2 asteroides dependiendo de su número de generaciones.Recuerda que no pueden existir más de 30
			//asteroides a la vez en la pantalla.
		}
	}
}
//onCollision(Entity* a) : recibe una entidad representando un asteroide que haya
//chocado con una bala, lo desactiva y genera otros 2 asteroides dependiendo de
//su número de generaciones.Recuerda que no pueden existir más de 30
//asteroides a la vez en la pantalla.

//En el método onCollision(Entity* a), al destruir un asteroide a la idea es
//desactivarlo y crear otros dos con generación como la de a menos uno(si el número de
//	generaciones de a es 0 no se genera nada).La posición de cada nuevo asteroide tiene
//	que ser cercana a la de a y tiene que moverse en una dirección aleatoria.
//	Por ejemplo, suponiendo que p y v son la velocidad y la posición de a, w su anchura, h
//	su altura, se puede usar el siguiente código para calcular la posición y velocidad de cada
//	asteroide nuevo :
//auto r = sdlutils().rand().nextInt(0, 360);
//auto pos = p + v.rotate(r) * 2 * std::max(w, h).
//auto vel = v.rotate(r) * 1.1f
//Recuerda que la anchura y altura del nuevo asteroide dependen de su número de
//generaciones.
