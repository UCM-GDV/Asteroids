#pragma once
#include "../../ecs/Component.h"
#include "../Transform.h"
#include <cassert>

class Follow : public Component {
private:
	Transform* transform;
	Transform* followObjectTransform;
public:
	// Constructora
	Follow(Transform* followObjectTransform_);
	// Destructora
	virtual ~Follow();
	// Inicializa el componente
	void initComponent();
	// Actualiza su vector de velocidad para perseguir al fighter
	void update();
};