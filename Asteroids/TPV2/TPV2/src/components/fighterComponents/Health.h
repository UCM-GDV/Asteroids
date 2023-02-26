#pragma once 
#include "../../ecs/Component.h"
#include "../../sdlutils/Texture.h"
#include "../../sdlutils/SDLUtils.h"

class Health : public Component {
private:
	int lives;
	Texture* texture;
public:
	Health() : texture(nullptr), lives(NUMBER_LIVES) {};
	void initComponent();
	void render();
	int getLives();
	void setLives(int lives_);
	void resetLives();
	virtual ~Health() {};
};
