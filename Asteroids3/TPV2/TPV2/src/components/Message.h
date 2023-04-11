#pragma once
#include "../game/ecs_def.h"
#include "../ecs/Entity.h"
#include "../utils/Vector2D.h"

struct Message {
	msgId_type id;
	// _m_ROUND_STARTED
	struct {

	} round_started;
	// _m_ROUND_FINISHED
	struct {

	} round_finished;
	// _m_FIGHTER_SHOOT
	struct {
		Vector2D pos, vel;
		double width, height;
	} fighter_shoot;
	//_m_BULLET_ASTEROID_COLLIDED
	struct {
		Entity* bullet;
		Entity* asteroid;
	} bullet_asteroid_coll;
};