#include "AsteroidsManager.h"
#include "../states/PlayState.h"
AsteroidsManager::AsteroidsManager(PlayState* m) : numasteroids(10), startTime(SDL_GetTicks()) {
	mngr_ = m;
}

AsteroidsManager::~AsteroidsManager() {}

void AsteroidsManager::createAsteroids(int n) {
	//añade nasteroides al juego
	for (int i = 0; i < n; i++) {
		if (numasteroids < 30) {
			int g, b;
			Vector2D p, c;
			float width, height, speed;
			g = sdlutils().rand().nextInt(1, 4);
			width = height = 10.0f + 5.0f * g;

			// elegimos su posición p de manera aleatoria en los bordes de la ventana
			b = sdlutils().rand().nextInt(0, 4);
			c = { WIN_WIDTH / 2 + (float) (sdlutils().rand().nextInt(-100, 101)), WIN_HEIGHT / 2 + (float)(sdlutils().rand().nextInt(-100, 101)) };

			if (b == 0) {
				p = { WIN_WIDTH + width , (float)(sdlutils().rand().nextInt(0, WIN_HEIGHT)) };
			}
			else if (b == 1) {
				p = { (float)(sdlutils().rand().nextInt(0, WIN_WIDTH)) , -(height) };
			}
			else if (b == 2) {
				p = { (float)(sdlutils().rand().nextInt(0, WIN_WIDTH)) , WIN_HEIGHT + width };
			}
			else if (b == 3) {
				p = { -(width), (float)(sdlutils().rand().nextInt(0, WIN_HEIGHT)) };
			}
			speed = (float)(sdlutils().rand().nextInt(1, 10) / 10.0f);
			Vector2D v = (c - p).normalize() * speed;

			asteroid = new Entity();
			asteroid->setContext(mngr_);
			asteroid->addComponent<Transform>(_TRANSFORM, p, v, width, height, 0);
			asteroid->addComponent<Generations>(_GENERATIONS, g);

			//tipo b
			if (sdlutils().rand().nextInt(0, 10) < 3) {
				asteroid->addComponent<FramedImage>(_FRAMEDIMAGE, &SDLUtils::instance()->images().at("YellowAsteroid"), width, height, ASTEROID_WHITE_NUMCOLS, ASTEROID_WHITE_NUMROWS);
				//asteroid->addComponent<Follow>(_FOLLOW);
			}
			//tipo a
			else {
				asteroid->addComponent<FramedImage>(_FRAMEDIMAGE, &SDLUtils::instance()->images().at("WhiteAsteroid"), width, height, ASTEROID_WHITE_NUMCOLS, ASTEROID_WHITE_NUMROWS);
			}
			mngr_->addEntity(asteroid);
			asteroid->addToGroup(_grp_ASTEROIDS);
			numasteroids++;
		}
	}	
}
void AsteroidsManager::addAsteroidFrequently() {
	//	genera un asteroide nuevo cada 5 segundos 
	uint32_t frameTime;
	frameTime = SDL_GetTicks() - startTime;
	if (frameTime >= ASTEROIDS_DELAY_TIME) {
		createAsteroids(1);
		startTime = SDL_GetTicks();
	}
}
void AsteroidsManager::destroyAllAsteroids() {
	//desactiva todos los asteroides actuales, usa la lista de grupo correspondiente del Manager.
	vector<Entity*> v = mngr_->getEntities(_grp_ASTEROIDS);
	for (auto& ents : v) {
		ents->setAlive(false);
	}
	
}

//recibe una entidad representando un asteroide que haya chocado con una bala
void AsteroidsManager::onCollision(Entity* a) {
	//lo desactiva 
	a->setAlive(false);
	
	Generations* g = a->getComponent<Generations>(_GENERATIONS);
	if (g != nullptr) {
		int gens = g->getGenerations();
		if (gens == 3 || gens == 2) {
			if (numasteroids < 30) {

			}
			//genera otros 2 asteroides dependiendo de su número de generaciones.Recuerda que no pueden existir más de 30
			//asteroides a la vez en la pantalla.
		}
	}
	
}
