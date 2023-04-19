#pragma once
#include "../ecs/Manager.h"
// Sistemas
#include "../systems/BulletSystem.h"
#include "../systems/CollisionsSystem.h"
#include "../systems/FighterSystem.h"
#include "../systems/NetWorkSystem.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/RenderSystem.h"
#include "../sdlutils/InputHandler.h"
#include "../systems/NetWorkSystem.h"
class PlayStateMultiPlayer : public Manager {
public:
	// Constructora
	PlayStateMultiPlayer();
	// Destructora
	~PlayStateMultiPlayer();
};