#pragma once
#ifndef ECS_DEF_H_
#define ECS_DEF_H_

using cmpId_type = int;
enum cmpId : cmpId_type {
	_TRANSFORM = 0,
	// ... (compoment ids)

	// do not remove this
	_LAST_CMP_ID
};
constexpr cmpId_type maxComponentId = _LAST_CMP_ID;

#endif // !ECS_DEF_H_