#pragma once
#include <cassert>
#include <math.h>
#include "../Transform.h" 
#include "../../ecs/Entity.h"
#include "../../ecs/Component.h"
#include "../../sdlutils/SDLUtils.h"
#include "../../sdlutils/InputHandler.h"
#include "../../components/fighterComponents/Gun.h"

class FighterControl : public Component {
	private:
		Transform* transform;
		FighterControl* fighterControl;
		Gun* gun;
	public:
		FighterControl();
		~FighterControl();
		void initComponent();
		void rotate(float r_);
		void acelerate();
		virtual void handleEvent(SDL_Event event);
		float degreesToRadians(float degree_);
};