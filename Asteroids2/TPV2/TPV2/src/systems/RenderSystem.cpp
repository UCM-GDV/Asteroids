#include "RenderSystem.h"
#include "../ecs/Manager.h"

// Constructora
RenderSystem::RenderSystem() {}
RenderSystem::RenderSystem(int state_) : state(state_), fighterTransform(nullptr), fighterHealth(nullptr), text(nullptr), textTransform(nullptr) {}

// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void RenderSystem::receive(const Message& m) {
	
}

// Inicializar el sistema, etc.
void RenderSystem::initSystem() {
	fighterTransform = mngr_->getSystem<FighterSystem>()->getFighterTransform();
	assert(fighterTransform != nullptr);
	fighterHealth = mngr_->getSystem<FighterSystem>()->getFighterHealth();
	assert(fighterHealth != nullptr);
}

// - Dibujar asteroides, balas y caza (sólo si el juego no está parado).
// - Dibujar las vidas (siempre).
// - Dibujar los mensajes correspondientes: si el juego está parado, etc (como en
// la práctica 1)
void RenderSystem::update() {
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 30, 50, 0);
	SDL_RenderClear(sdlutils().renderer());

	// Caza
	dest = build_sdlrect(fighterTransform->getPos(), fighterTransform->getW(), fighterTransform->getH());
	sdlutils().images().at("Fighter").render(dest, fighterTransform->getR());

	// Vidas
	for (int i = 0; i < fighterHealth->getlife(); ++i) {
		Vector2D healthPosition = Vector2D(i * LIVES_WIDTH + LIVES_POSITION.getX(), LIVES_POSITION.getY());
		dest = build_sdlrect(healthPosition, LIVES_WIDTH, LIVES_HEIGHT);
		sdlutils().images().at("Life").render(dest);
	}

	// Si esta en PlayState
	if (state == 1) {
		// Asteroides
		for (Entity* ast : mngr_->getEntities(_grp_ASTEROIDS_WHITE)) {
			renderAsteroid(ast, &sdlutils().images().at("WhiteAsteroid"));
		}
		for (Entity* ast : mngr_->getEntities(_grp_ASTEROIDS_YELLOW)) {
			renderAsteroid(ast, &sdlutils().images().at("YellowAsteroid"));
		}
		// Balas
		for (Entity* bullet : mngr_->getEntities(_grp_BULLETS)) {
			bulletTransform = mngr_->getComponent<Transform>(bullet);
			dest = build_sdlrect(bulletTransform->getPos(), bulletTransform->getW(), bulletTransform->getH());
			sdlutils().images().at("Bullet").render(dest, bulletTransform->getR());
		}
	}
	// Mensajes en el resto de estados (PauseState y EndState)
	else if (state == 0 || state == 2) {
		for (Entity* text : mngr_->getEntities(_grp_MESSAGES)) {
			textTransform = mngr_->getComponent<Transform>(text);
			dest = build_sdlrect(textTransform->getPos(), textTransform->getW(), textTransform->getH());
			mngr_->textTextures_[text]->render(dest, textTransform->getR());
		}
	}

	SDL_RenderPresent(sdlutils().renderer());
}

// FRAMEDIMAGE
void RenderSystem::renderAsteroid(Entity* a, Texture* tex) {
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
	tex->render(src, dest);
}

