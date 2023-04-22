#include "RenderSystem.h"
#include "../ecs/Manager.h"

// Constructoras
RenderSystem::RenderSystem() : state(-1), fighterTransform(nullptr), fighterHealth(nullptr), auxTransform(nullptr) {}
RenderSystem::RenderSystem(int state_) : state(state_), fighterTransform(nullptr), fighterHealth(nullptr), auxTransform(nullptr) {}

// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void RenderSystem::receive(const Message& m) {}

// Inicializar el sistema, etc.
void RenderSystem::initSystem() {
	if (state == 0 || state == 1 || state == 2) {
		fighterTransform = mngr_->getSystem<FighterSystem>()->getFighterTransform();
		assert(fighterTransform != nullptr);
		fighterHealth = mngr_->getSystem<FighterSystem>()->getFighterHealth();
		assert(fighterHealth != nullptr);
	}
	else if (state == 3) {
		fighterTransform1 = mngr_->getSystem<FighterSystem>()->getFighterTransform1();
		fighterHealth1 = mngr_->getSystem<FighterSystem>()->getFighterHealth1();
		fighterTransform2 = mngr_->getSystem<FighterSystem>()->getFighterTransform2();
		fighterHealth2 = mngr_->getSystem<FighterSystem>()->getFighterHealth2();
	}
}

// - Dibujar asteroides, balas y caza (sólo si el juego no está parado).
// - Dibujar las vidas (siempre).
// - Dibujar los mensajes correspondientes: si el juego está parado, etc (como en
// la práctica 1)
void RenderSystem::update() {
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 30, 50, 0);
	SDL_RenderClear(sdlutils().renderer());
	switch (state)
	{
		case -1:
			//Main Menu
			for (Entity* ui : mngr_->getEntities(_grp_UI)) {
				renderUI(ui);
			}
			break;
		case 0:
			//Pausa 
			renderFighter(fighterTransform, "Fighter");
			renderLives(fighterHealth, LIVES_POSITION, "Life");
			for (Entity* ui : mngr_->getEntities(_grp_UI)) {
				renderUI(ui);
			}
			break;
		case 1:
			//PLAY
			renderFighter(fighterTransform, "Fighter");
			renderLives(fighterHealth, LIVES_POSITION, "Life");
			// Asteroides
			for (Entity* ast : mngr_->getEntities(_grp_ASTEROIDS_WHITE)) {
				renderAsteroid(ast, "WhiteAsteroid");

			}
			for (Entity* ast : mngr_->getEntities(_grp_ASTEROIDS_YELLOW)) {
				renderAsteroid(ast, "YellowAsteroid");
			}
			for (Entity* bullet : mngr_->getEntities(_grp_BULLETS)) {
				renderBullet(bullet, "Bullet");
			}
			break;
		case 2:
			//FINAL
			renderFighter(fighterTransform, "Fighter");
			renderLives(fighterHealth, LIVES_POSITION, "Life");
			for (Entity* ui : mngr_->getEntities(_grp_UI)) {
				renderUI(ui);
			}

			break;
		case 3:
			// PLAY MULTYPLAYER
			renderFighter(fighterTransform1, "Fighter");
			renderFighter(fighterTransform2, "Fighter");
			renderLives(fighterHealth1, LIVES_1_POSITION, "Life");
			renderLives(fighterHealth2, LIVES_2_POSITION, "Life");
			for (Entity* bullet : mngr_->getEntities(_grp_BULLETS)) {
				renderBullet(bullet, "Bullet");
			}
			
			for (Entity* ui : mngr_->getEntities(_grp_UI)) {
				renderUI(ui);
			}
			break;
		default:
			break;
	}

	SDL_RenderPresent(sdlutils().renderer());
}

// FRAMEDIMAGE
void RenderSystem::renderAsteroid(Entity* a, string key) {
	asteroidTrasform = mngr_->getComponent<Transform>(a);
	asteroidFramedImage = mngr_->getComponent<FramedImage>(a);

	fw = asteroidFramedImage->getFrameWidth();
	fh = asteroidFramedImage->getFrameHeight();
	numCols = asteroidFramedImage->getNumCols();
	numRows = asteroidFramedImage->getNumRows();;
	currentframe = asteroidFramedImage->getCurrentFrame();

	asteroidFramedImage->setCurrentFrame((currentframe + 1) % (numCols * numRows - 1));

	dest = build_sdlrect(asteroidTrasform->getPos(), asteroidTrasform->getW(), asteroidTrasform->getH());

	src.x = (currentframe % numCols) * fw;
	src.y = (currentframe / numCols) * fh;
	src.w = fw;
	src.h = fh;
	sdlutils().images().at(key).render(src, dest);
}

void RenderSystem::renderFighter(Transform* tr, string key) {
	dest = build_sdlrect(tr->getPos(), tr->getW(), tr->getH());
	sdlutils().images().at(key).render(dest, tr->getR());
}

void RenderSystem::renderLives(Health* health, Vector2D initialPos, string key) {
	for (int i = 0; i < health->getlife(); ++i) {
		Vector2D healthPosition = Vector2D(i * LIVES_WIDTH + initialPos.getX(), initialPos.getY());
		dest = build_sdlrect(healthPosition, LIVES_WIDTH, LIVES_HEIGHT);
		sdlutils().images().at(key).render(dest);
	}
}
void RenderSystem::renderBullet(Entity* b, string key) {
	bulletTransform = mngr_->getComponent<Transform>(b);
	dest = build_sdlrect(bulletTransform->getPos(), bulletTransform->getW(), bulletTransform->getH());
	sdlutils().images().at(key).render(dest, bulletTransform->getR());
}

void RenderSystem::renderUI(Entity* t) {
	auxTransform = mngr_->getComponent<Transform>(t);
	dest = build_sdlrect(auxTransform->getPos(), auxTransform->getW(), auxTransform->getH());
	mngr_->UITextures_[t]->render(dest, auxTransform->getR());
}
