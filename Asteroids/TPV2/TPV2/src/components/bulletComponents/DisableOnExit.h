#pragma once
#include "../Transform.h" 
#include "../../ecs/Entity.h"
#include <cassert>

class DisableOnExit : public Component {
private:
	Transform* transform;
public:
	DisableOnExit();
	void initComponent();
	void update();
	virtual ~DisableOnExit();
protected:
};