#pragma once
#ifndef PLAY_STATE_H_
#define PLAY_STATE_H_
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
class PlayState : public Manager {
private:
	Entity* fighter = nullptr;
	Transform* fighterTransform = nullptr;
	Gun* fighterGun = nullptr;
	FighterControl* fighterControl = nullptr;
	Entity* bullet = nullptr;
	
public:
	// Constructora
	PlayState();
	// Destructora
	~PlayState();
	// Anade bala a la escena dependiendo de la posicion del fighter
	void addBullet();
	void handleEvent() { 
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			fighterControl->handleEvent(event);
			fighterGun->handleEvent(event);
		}
	};//teneis que hacer el handle event de vustro componente

};
#endif