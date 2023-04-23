#pragma once
#include "../game/ecs_def.h"
#include "../ecs/Entity.h"
#include "../utils/Vector2D.h"

struct Message {
	msgId_type id;
	// _m_FIGHTER_SHOOT
	struct {
		Vector2D pos, vel;
		float rot;
		double width, height;
	} fighter_shoot;
	// _m_FIGHTER_UPDATE
	struct {
		Vector2D pos, vel;
		float rot;
		double width, height;
	} fighter_update;
	//_m_BULLET_ASTEROID_COLLIDED
	struct {
		Entity* bullet;
		Entity* asteroid;
	} bullet_asteroid_coll;
	// _m_FIGHTERPOSUP
	struct {
		Vector2D pos, vel;
		float rot;
		double width, height;
	} fighterposup;
	// _m_ADD_BULLET
	struct {
		Vector2D pos, vel;
		float rot;
	} add_bullet;
	// _m_FIGHTER_BULLET_COLLIDED
	struct {
		int fighterHealth;
	} fighter_bullet_coll;
};