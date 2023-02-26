#pragma once
#ifndef ECS_DEF_H_
#define ECS_DEF_H_

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

#endif // !ECS_DEF_H_