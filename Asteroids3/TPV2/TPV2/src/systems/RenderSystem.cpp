#include "RenderSystem.h"
#include "../ecs/Manager.h"
#include "NetWorkSystem.h"
#include "GameCtrlSystem.h"
// Constructoras
RenderSystem::RenderSystem() : state(-1), fighterTransform(nullptr), fighterHealth(nullptr), auxTransform(nullptr) {}
RenderSystem::RenderSystem(int state_) : state(state_), fighterTransform(nullptr), fighterHealth(nullptr), auxTransform(nullptr) {}

// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
void RenderSystem::receive(const Message& m) {
	switch (m.id) {
	case _m_CHANGE_STATE: onChangeState(); break;
	default: break;
	}
}
void RenderSystem::onChangeState() {
	state = 3;
	fighterTransform1 = mngr_->getSystem<FighterSystem>()->getFighterTransform1();
	fighterHealth1 = mngr_->getSystem<FighterSystem>()->getFighterHealth1();
	fighterTransform2 = mngr_->getSystem<FighterSystem>()->getFighterTransform2();
	fighterHealth2 = mngr_->getSystem<FighterSystem>()->getFighterHealth2();

	name = mngr_->getSystem<GameCtrlSystem>()->getname();
}
// Inicializar el sistema, etc.
void RenderSystem::initSystem() {
	if (state == 0 || state == 1 || state == 2) {
		fighterTransform = mngr_->getSystem<FighterSystem>()->getFighterTransform();
		assert(fighterTransform != nullptr);
		fighterHealth = mngr_->getSystem<FighterSystem>()->getFighterHealth();
		assert(fighterHealth != nullptr);
	}
}

// - Dibujar asteroides, balas y caza (s�lo si el juego no est� parado).
// - Dibujar las vidas (siempre).
// - Dibujar los mensajes correspondientes: si el juego est� parado, etc (como en
// la pr�ctica 1)
void RenderSystem::update() {
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 30, 50, 0);
	SDL_RenderClear(sdlutils().renderer());
	switch (state) {
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
			// PLAY MULTIPLAYER
			renderFighter(fighterTransform1, "Fighter");
			renderFighter(fighterTransform2, "Fighter");
			renderLives(fighterHealth1, LIVES_1_POSITION, "Life");
			renderLives(fighterHealth2, LIVES_2_POSITION, "Life");
			for (Entity* bullet : mngr_->getEntities(_grp_BULLETS)) {
				renderBullet(bullet, "Bullet");
			}
			renderUIname();
			
			
			break;
		case 4: case 5:
            for (Entity* ui : mngr_->getEntities(_grp_UI)) {
				renderUI(ui);
            }
			break;
		default: break;
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

void RenderSystem::renderUIname() {
	if (mngr_->getEntities(_grp_UI).size() >= 2) {
		Entity* name1 = mngr_->getEntities(_grp_UI)[0];
		Entity* name2 = mngr_->getEntities(_grp_UI)[1];
		Vector2D pos1 = fighterTransform1->getPos() + Vector2D(0, 30);
		Vector2D pos2 = fighterTransform2->getPos() + Vector2D(0, 30);
		if (mngr_->getSystem<NetworkSystem>()->getServer()) {
			auxTransform = mngr_->getComponent<Transform>(name1);
			dest = build_sdlrect(pos1, auxTransform->getW(), auxTransform->getH());
			mngr_->UITextures_[name1]->render(dest, auxTransform->getR());
			auxTransform = mngr_->getComponent<Transform>(name2);
			dest = build_sdlrect(pos2, auxTransform->getW(), auxTransform->getH());
			mngr_->UITextures_[name2]->render(dest, auxTransform->getR());
		}
		else {
			auxTransform = mngr_->getComponent<Transform>(name1);
			dest = build_sdlrect(pos2, auxTransform->getW(), auxTransform->getH());
			mngr_->UITextures_[name1]->render(dest, auxTransform->getR());
			auxTransform = mngr_->getComponent<Transform>(name2);
			dest = build_sdlrect(pos1, auxTransform->getW(), auxTransform->getH());
			mngr_->UITextures_[name2]->render(dest, auxTransform->getR());
		}
	}
}