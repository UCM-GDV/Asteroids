#pragma once
#include "../ecs/Manager.h"
// Sistemas
#include "../systems/AsteroidsSystem.h"
#include "../systems/BulletSystem.h"
#include "../systems/CollisionsSystem.h"
#include "../systems/FighterSystem.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/RenderSystem.h"
#include "../sdlutils/InputHandler.h"

class PlayState : public Manager {
public:
	// Constructora
	PlayState();
	// Destructora
	~PlayState();

};