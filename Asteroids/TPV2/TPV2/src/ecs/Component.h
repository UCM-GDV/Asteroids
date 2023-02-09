#pragma once
#ifndef COMPONENT_H_
#define COMPONENT_H_
#include "../game/ecs_def.h"
class Manager;
class Entity;
using namespace std;

class Component {
public:
	// Constructora
	Component() : ent_(), mngr_() {}
	// Destructora
	virtual ~Component() { }
	// Asigna al componente su entidad (gameObject) y su manager
	inline void setContext(Entity* ent, Manager* mngr) {
		ent_ = ent;
		mngr_ = mngr;
	}
	// Inicializa el componente
	virtual void initComponent() { }
	// Actualiza el componente
	virtual void update() { }
	// Renderiza el componente
	virtual void render() { }
protected:
	Entity* ent_;
	Manager* mngr_;
};
#endif