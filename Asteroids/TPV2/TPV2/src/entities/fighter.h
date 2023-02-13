#pragma once
#ifndef FIGHTER_H_
#define FIGHTER_H_
#include "../ecs/Entity.h"
#include "../game/Game.h"
#include "../game/ecs_def.h"
#include "../components/Image.h"
#include "../sdlutils/SDLUtils.h"

class Fighter : public Entity {
private:
	Transform* transform;
public:
	// Constructora
	Fighter(Game* _game);
	void update();
	void handleEvent();
	// Destructora
	~Fighter();
protected:
};
#endif // !FIGHTER_H_
