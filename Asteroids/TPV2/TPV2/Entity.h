#pragma once
#include "Component.h"
using namespace std;

class Entity {
public:
	Entity();
	virtual ~Entity();
	inline void setContext(Manager* mngr);
	inline bool isAlive();
	inline void setAlive(bool alive);
private:
	bool alive_;
	Manager* mngr_;
	vector<Component*> currCmps_;
	//array<Component*, ecs::maxComponentId> cmps_;
};