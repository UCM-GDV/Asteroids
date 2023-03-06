#pragma once
#include "../ecs/Component.h"
#include "Transform.h"
#include "../ecs/Entity.h"
#include <cassert>

class ShowAtOppositeSide : public Component {
private:
	Transform* transform;
public:
	// Constructora
	ShowAtOppositeSide();
	// Destructora
	virtual ~ShowAtOppositeSide();
	// Inicializa el componente
	void initComponent();
	// Actualiza el componente
	void update();
	
};