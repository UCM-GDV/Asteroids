#pragma once
#include "../ecs/Component.h"
#include "Transform.h"
#include "../ecs/Entity.h"
#include <cassert>

class ShowAtOppositeSide : public Component {
private:
	Transform* transform;
	//PlayState* playState;
public:
	// Constructora
	ShowAtOppositeSide();
	
	void initComponent();
	void update();
	// Destructora
	virtual ~ShowAtOppositeSide();
};