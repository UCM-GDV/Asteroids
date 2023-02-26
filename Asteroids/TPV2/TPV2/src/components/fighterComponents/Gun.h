#pragma once
#include "../../ecs/Component.h"
#include "../Transform.h"
#include "../../ecs/Entity.h"
#include "../../entities/bullet.h"
#include "../../states/PlayState.h"
#include <cassert>

class Gun : public Component {
private:
	Transform* transform;
public:
	// Constructora
	Gun();
	// Destructora
	virtual ~Gun();
	// Inicializa el componente
	void initComponent();
	void tryShoot();
};