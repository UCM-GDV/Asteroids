#pragma once
#include "../Transform.h" 
#include "../../ecs/Entity.h"
#include <cassert>

struct DisableOnExit : public Component {
private:
	Transform* transform;
public:
    // Identificador
    constexpr static cmpId_type id = _DISABLEONEXIT;
	// Constructora
	DisableOnExit();
	// Destructora
	virtual ~DisableOnExit();
	// Inicializa el componente
	void initComponent();
	// Actualiza el componente
	void update();
};