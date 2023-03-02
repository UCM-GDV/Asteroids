#pragma once
#include "../Transform.h" 
#include "../../ecs/Entity.h"
#include <cassert>

class DisableOnExit : public Component {
private:
	Transform* transform;
public:
	// Constructora
	DisableOnExit();
	// Destructora
	virtual ~DisableOnExit();
	// Inicializa el componente
	void initComponent();
	// Actualiza el componente
	void update();
};