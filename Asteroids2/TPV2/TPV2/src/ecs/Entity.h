#pragma once
#include "Component.h"
#include <vector>
#include <array>
using namespace std;

class Entity {
private:
	friend Manager;
	Manager* mngr_;
	vector<Component*> currCmps_;
	array<Component*, maxComponentId> cmps_;
	bool alive_;
	grpId_type gId_;
public:
	// Constructora
	Entity(grpId_type gId) {}
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;
	// Destructora
	virtual ~Entity() {
		for (auto c : currCmps_) {
			delete c;
		}
	}
	// Asigna a la entidad su manager
	inline void setContext(Manager* mngr) { mngr_ = mngr; }
	// Devuelve si esta vivo
	inline bool isAlive() { return alive_; }
	// Establece si esta vivo o no
	inline void setAlive(bool alive) { alive_ = alive; }
	// Inicializa componente
	virtual void initComponent() {} 
};