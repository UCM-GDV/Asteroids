#pragma once
#include <cassert>
#include "../game/constants.h"
#include "../components/Message.h"
class Manager;
class System {
public:
	System() { }
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