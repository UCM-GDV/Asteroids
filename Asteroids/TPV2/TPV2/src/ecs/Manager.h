#pragma once
#include <vector>
#include <array>
#include "Entity.h"
class Game;
using namespace std;

class Manager {
public:
	// Constructora
	Manager() : ents_() { ents_.reserve(100); }
	// Destructora
	virtual ~Manager() {
		for (auto e : ents_) {
			delete e;
		}
	}
	// Anade una entidad
	template<typename T>
	Entity* addEntity(T* e){
		e->setAlive(true);
		e->setContext(this);
		 ents_.push_back(e);
		return e;
	}
	// Devuelve el vector de entidades
	inline const auto& getEntities() { return ents_; }
	// Devuelve el vector de entidades por ID de grupo
	//inline const auto& getEntitiesByGroup(grpId_type gId) { return entsByGroup_[gId]; }
    // Borra entidades no vivas
	void refresh(){
		// Erase borra todos los elementos desde un inicio a un fin 
		ents_.erase(remove_if(ents_.begin(), ents_.end(), [](Entity* e) {
            if (e->isAlive()) {
                return false;
            }
            else {
                delete e;
                return true;
            }
            }), 
        ents_.end());
	}
	// Actualiza todas las entidades
	void update() {
		auto n = ents_.size();
		for (auto i = 0u; i < n; i++)
			ents_[i]->update();
	}
	// Dibuja todas las entidades
	void render() const {
		auto n = ents_.size();
		for (auto i = 0u; i < n; i++)
			ents_[i]->render();
	}
	// Manejo de los eventos de todas las entidades
	virtual void handleEvent() {
		auto n = ents_.size();
		for (auto i = 0u; i < n; i++)
			ents_[i]->handleEvent();
	}
private:
	vector<Entity*> ents_;
	//array<vector<Entity*>, maxGroupId> entsByGroup_;
};