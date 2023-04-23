#pragma once
#include "../game/ecs_def.h"
#include "../ecs/Entity.h"
#include "../utils/Vector2D.h"
#include <string>
using namespace std;
struct Messagenet {
	msgnetId_type id;
	char name[10];
	// _m_FIGHTERPOSUP
	struct {
		Vector2D pos, vel;
		double width, height;
		float rot;
	} fighter_update;
	// _m_ADDBULLET
	struct {
		Vector2D pos, vel;
		float rot;
	} add_bullet;
};