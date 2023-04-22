#pragma once
#include "../game/ecs_def.h"
#include "../ecs/Entity.h"
#include "../utils/Vector2D.h"

struct Messagenet {
	msgnetId_type id;
	// _m_CONNECTED
	struct {

	} round_started;
	struct {
		Vector2D pos, vel;
		double width, height;
		float rot;
	} fighter_update;
};