#pragma once
#include "../Transform.h" 
#include "../../ecs/Entity.h"
#include <cassert>

class DeAcceleration : public Component {
private:
	Transform* transform;
public:
	DeAcceleration();
	void initComponent();
	void update();
	virtual ~DeAcceleration() {};
protected:
};