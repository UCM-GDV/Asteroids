#pragma once
#include <cassert>
#include <math.h>
#include "../Transform.h" 
#include "../../ecs/Entity.h"
#include "../../ecs/Component.h"
#include "../../sdlutils/SDLUtils.h"

class FighterControl : public Component {
	private:
		Transform* transform;
	public:
		FighterControl();
		~FighterControl();
		void initComponent();
		void rotate(float r_);
		void acelerate();
		float degreesToRadians(float degree_);
};