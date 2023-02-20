#pragma once
#ifndef DEACCELERATION_H_
#define DEACCELERATION_H_
#include "../Transform.h" 
#include "../../ecs/Entity.h"

class DeAcceleration : public Component {
private:
	Transform* transform;
public:
	DeAcceleration();
	void initComponent();
	void update();
protected:
};
#endif