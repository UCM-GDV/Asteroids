#pragma once 
#ifndef HEALTH_H_
#define HEALTH_H_
#include "../../ecs/Component.h"
#include "../../sdlutils/Texture.h"
#include "../../sdlutils/SDLUtils.h"

class Health : public Component {
private:
	int lives;
	Texture* texture;
public:
	Health() : texture(nullptr), lives(3) {};
	void initComponent();
	void render();
	virtual ~Health() {};
};
#endif // !HEALTH_H_
