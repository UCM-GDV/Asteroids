#pragma once
#include "Component.h"
#include <vector>
#include <array>
using namespace std;

class Entity {
protected:
	Manager* mngr_;
private:
	friend Manager;

	vector<Component*> currCmps_;
	array<Component*, maxComponentId> cmps_;
	bool alive_;
	grpId_type gId_;
public:
	// Constructora
	Entity() : mngr_(nullptr), cmps_(), currCmps_(), alive_() { currCmps_.reserve(maxComponentId); }
	Entity(grpId_type gId) : mngr_(nullptr), cmps_(), currCmps_(), alive_(), gId_(gId) { currCmps_.reserve(maxComponentId); }
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
	// Crea un componente
	template<typename T, typename ...Ts>
	inline T* addComponent(cmpId_type cId, Ts && ...args) {	
		T* c = new T(forward<Ts>(args)...);
		// Borra el componente actual de la posicion cId en caso 
		// de encontrar el component
		removeComponent(cId);
		// Anade al array y a la lista de componentes
		currCmps_.push_back(c);
		cmps_[cId] = c;
		// Inicializa el componente
		c->setContext(this, mngr_);
		c->initComponent();
		return c;
	}
	// Quita un componente
	inline void removeComponent(cmpId_type cId) {
		// Si hay componente en la posición  
		if (cmps_[cId] != nullptr) {
			// Busca en el array de todos los componentes
			auto iter = find(currCmps_.begin(), currCmps_.end(), cmps_[cId]);
			// Lo borra de la lista de componentes 
			currCmps_.erase(iter);
			// Lo borra del objeto
			delete cmps_[cId];
			// Lo quita del array de componentes
			cmps_[cId] = nullptr;
		}
	}
	// Devuelve el componente
	template<typename T>
	inline T* getComponent(cmpId_type cId) {
		return static_cast<T*>(cmps_[cId]);
	}
	// Comprueba si tiene un componente
	inline bool hasComponent(cmpId_type cId) {
		return cmps_[cId] != nullptr;
	}
	// Actualiza recorriendo la lista de componentes
	inline void update() {
		auto n = currCmps_.size();
		for (auto i = 0u; i < n; i++)
			currCmps_[i]->update();
	}
	// Dibuja recorriendo la lista de componentes
	inline void render() {
		auto n = currCmps_.size();
		for (auto i = 0u; i < n; i++)
			currCmps_[i]->render();
	}
	// Manejo de los eventos a traves del InputHandler
	virtual void handleEvent() {}
};