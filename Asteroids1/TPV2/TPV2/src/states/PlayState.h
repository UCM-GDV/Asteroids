#pragma once
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "../game/ecs_def.h"
#include "../components/Image.h"
#include "../components/asteroidsComponents/FramedImage.h"
#include "../components/fighterComponents/DeAcceleration.h"
#include "../components/fighterComponents/Health.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/fighterComponents/FighterControl.h"
#include "../components/fighterComponents/Gun.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/bulletComponents/DisableOnExit.h"
#include "../components/asteroidsComponents/Generations.h"
#include "../components/asteroidsComponents/Follow.h"
#include "../game/AsteroidsManager.h"
#include "../game/CollisionsManager.h"
#include "../game/Game.h"

class PlayState : public Manager {
private:
	Entity* fighter;
	Transform* fighterTransform;
	Gun* fighterGun;
	FighterControl* fighterControl;
	Health* fighterHealth;
	Entity* bullet;
	Game* game;
public:
	// Constructora
	PlayState(Game* game);
	// Destructora
	~PlayState();
	// Anade bala a la escena dependiendo de la posicion del fighter
	void addBullet();
    // Recoge el input del usuario
	void handleEvent();
    // Actualiza el vector de entidades, anade asteroides y comprueba las colisiones
	void update();
	// Devuelve el puntero al fighter
	inline Entity* getFighter() { return fighter; }
	// Devuelve el puntero al game
	inline Game* getGame() { return game; }
	// Reestablece la posicion, velocidad y rotacion del fighter
    inline void resetFighter() {
        fighterTransform->setPos({ WIN_HALF_WIDTH, WIN_HALF_HEIGHT });
        fighterTransform->setVel(FIGHTER_VELOCITY);
        fighterTransform->setRot(0);
	}
	inline int getLives() { return fighterHealth->getLives(); }
	// Decrementa el numero de vidas actual
	inline void decreaseLives() { fighterHealth->decreaseLive(); }
	// Resetea el numero de vidas actual
	inline void resetLives() { fighterHealth->setLives(NUMBER_LIVES); }
	// Para el juego
	void pauseGame();
	// Fin del juego
    void endGame(string result);
};