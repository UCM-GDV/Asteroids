#pragma once
#include "../../ecs/Component.h"
#include "../Transform.h"
#include <cassert>

struct Follow : public Component {
private:
	Transform* transform;
	Transform* followObjectTransform;
public:
	// Identificador
	constexpr static cmpId_type id = _FOLLOW;
	// Constructora
	Follow(Transform* followObjectTransform_);
	// Destructora
	virtual ~Follow();
	// Inicializa el componente
	void initComponent();
	// Actualiza su vector de velocidad para perseguir al fighter
	void update();
};