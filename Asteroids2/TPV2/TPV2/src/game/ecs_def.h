#pragma once
#include "../utils/Vector2D.h"
using cmpId_type = int;
enum cmpId : cmpId_type {
	_TRANSFORM = 0,
	//_IMAGE = 1,
	_FRAMEDIMAGE = 1,
	//_DEACCELERATION = 3,
	_HEALTH = 2,
	//_FIGHTERCONTROL = 5,
	//_GUN = 6,
	//_SHOWATOPPOSITESIDE = 7,
	_GENERATIONS = 3,
	//_FOLLOW = 9,
	//_DISABLEONEXIT = 10,
	// do not remove this
	_LAST_CMP_ID
};
constexpr cmpId_type maxComponentId = _LAST_CMP_ID;

using grpId_type = int;
enum grpId : grpId_type {
    _grp_GENERAL = 0, 
	_grp_ASTEROIDS_WHITE = 1,
	_grp_ASTEROIDS_YELLOW = 2,
	_grp_BULLETS = 3,
	_grp_FIGHTER = 4,
	_grp_MESSAGES = 5,
	// do not remove this
	_LAST_GRP_ID
};
constexpr grpId_type maxGroupId = _LAST_GRP_ID;

using sysId_type = int;
enum sysId : sysId_type {
	_sys_ASTEROIDS = 0,
	_sys_BULLET = 1,
	_sys_COLLISIONS = 2,
	_sys_FIGHTER = 3,
	_sys_GAMECTRL = 4,
	_sys_RENDER = 5,
	// do not remove this
	_LAST_SYS_ID
};
constexpr sysId_type maxSystemId = _LAST_SYS_ID;

using msgId_type = int;
enum msgId : msgId_type {
	_m_ROUND_STARTED,
	_m_ROUND_FINISHED,
	_m_FIGTHER_ASTEROID_COLLIDED,
	_m_BULLET_ASTEROID_COLLIDED,
	_m_FIGHTER_SHOOT,
	_m_ASTEROIDS_EXTINCTION,
	_m_UPDATE_POSITION,
};

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

};