#pragma once
#include "../../ecs/Component.h"
#include "../Transform.h"

class Follow : public Component {
private:
	Transform* transform;
	Transform* followObjectTransform;
public:
	// Constructora
	Follow(Transform* followObjectTransform_);
	// Destructora
	~Follow();
	void initComponent();
	void update();
};