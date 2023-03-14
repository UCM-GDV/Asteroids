#pragma once
#include "../ecs/Component.h"
#include "Transform.h"
#include "../ecs/Entity.h"
#include <cassert>

struct ShowAtOppositeSide : public Component {
private:
	Transform* transform;
public:
    // Identificador
    constexpr static cmpId_type id = _SHOWATOPPOSITESIDE;
	// Constructora
	ShowAtOppositeSide();
	// Destructora
	virtual ~ShowAtOppositeSide();
	// Inicializa el componente
	void initComponent();
	// Actualiza el componente
	void update();
	
};