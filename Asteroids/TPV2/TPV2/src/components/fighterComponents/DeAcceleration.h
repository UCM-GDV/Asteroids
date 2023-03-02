#pragma once
#include "../Transform.h" 
#include "../../ecs/Entity.h"
#include <cassert>

class DeAcceleration : public Component {
private:
	// Referencia al Transform
	Transform* transform;
public:
	// Constructora
	DeAcceleration();
	// Destructora
	virtual ~DeAcceleration();
	// Inicializa el componente
	void initComponent();
	// Actualiza el componente
	void update();
};