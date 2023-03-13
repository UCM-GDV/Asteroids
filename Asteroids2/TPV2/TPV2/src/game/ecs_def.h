#pragma once
using cmpId_type = int;
enum cmpId : cmpId_type {
	_TRANSFORM = 0,
	_IMAGE = 1,
	_FRAMEDIMAGE = 2,
	_DEACCELERATION = 3,
	_HEALTH = 4,
	_FIGHTERCONTROL = 5,
	_GUN = 6,
	_SHOWATOPPOSIDESIDE = 7,
	_GENERATIONS = 8,
	_FOLLOW = 9,
	_DISABLEONEXIT = 10,
	// do not remove this
	_LAST_CMP_ID
};
constexpr cmpId_type maxComponentId = _LAST_CMP_ID;

using grpId_type = int;
enum grpId : grpId_type {
    _grp_GENERAL = 0, 
	_grp_ASTEROIDS = 1,
	_grp_BULLETS = 2,
	_grp_FIGHTER = 3,
	_grp_MESSAGES =4,
	_LAST_GRP_ID
};
constexpr grpId_type maxGroupId = _LAST_GRP_ID;

using sysId_type = int;
enum sysId : sysId_type {
	_sys_ASTEROIDS = 0,
	_sys_COLLISIONS,
	// do not remove this
	_LAST_SYS_ID
};
constexpr sysId_type maxSystemId = _LAST_SYS_ID;

using msgId_type = int;
enum msgId : msgId_type {
	_m_ASTEROIDS_END, //
	_m_ASTEROIDS_ADD
};

struct Message {
	msgId_type id;
	// _m_ASTEROIDS_END
	struct {
		Entity* e;
	} asteroids_end;
	// _m_ASTEROIDS_ADD
	struct {
		unsigned int n;
	} add_asteroids_data;
};