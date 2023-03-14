#pragma once
#include "../game/ecs_def.h"
#include "Manager.h"
#include "../game/constants.h"

class System {
public:
	virtual ~System() { }
	void setContext(Manager* mngr) {
		mngr_ = mngr;
	}
	virtual void initSystem() { }
	virtual void update() { }
	virtual void receive(const Message& m) { }
protected:
	Manager* mngr_;
};