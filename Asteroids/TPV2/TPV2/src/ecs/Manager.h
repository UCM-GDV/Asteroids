#pragma once
#include <vector>
#include <array>
#include "Entity.h"
class Game;
using namespace std;

class Manager {
public:
	// Constructora
	Manager() : entsByGroup_() {
		for (auto& groupEntities : entsByGroup_) {
			groupEntities.reserve(100);
		}
	}
	// Destructora
	virtual ~Manager() {
		for (auto& ents : entsByGroup_) {
			for (auto e : ents) {
				delete e;
			}
		}
	}
	// Anade una entidad
	template<typename T>
	Entity* addEntity(T* e, grpId_type gId = _grp_GENERAL){
		e->setAlive(true);
		e->setContext(this);
		entsByGroup_[gId].push_back(e);
		return e;
	}
	// Devuelve el vector de entidades
	inline const auto& getEntities(grpId_type gId = _grp_GENERAL) {
		return entsByGroup_[gId];
	}
    // Borra entidades no vivas
	void refresh(){
		for (grpId_type gId = 0; gId < maxGroupId; gId++) {
			auto& grpEnts = entsByGroup_[gId];
			grpEnts.erase(
				std::remove_if(grpEnts.begin(), grpEnts.end(),
					[](Entity* e) {
						if (e->isAlive()) {
							return false;
						}
						else {
							delete e;
							return true;
						}
					}),
				grpEnts.end());
		}
	}
	// Actualiza todas las entidades
	virtual void update() {
		for (auto& ents : entsByGroup_) {
			auto n = ents.size();
			for (auto i = 0u; i < n; i++)
				ents[i]->update();
		}
	}
	// Dibuja todas las entidades
	void render() const {
		for (auto& ents : entsByGroup_) {
			auto n = ents.size();
			for (auto i = 0u; i < n; i++)
				ents[i]->render();
		}
	}
	// Manejo de los eventos de todas las entidades
	virtual void handleEvent() {
		for (auto& ents : entsByGroup_) {
			auto n = ents.size();
			for (auto i = 0u; i < n; i++)
				ents[i]->handleEvent();
		}
	}
private:
	array<vector<Entity*>, maxGroupId> entsByGroup_;
};