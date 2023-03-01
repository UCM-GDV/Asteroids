#pragma once
#include "../../ecs/Component.h"
#include "../Transform.h"
#include "../../ecs/Entity.h"
#include <cassert>
class PlayState;

class Gun : public Component {
private:
	Transform* transform;
	int startTime;
public:
	// Constructora
	Gun();
	// Destructora
	virtual ~Gun();
	// Inicializa el componente
	void initComponent();
	void handleEvent(SDL_Event event);
	void tryShoot();
};