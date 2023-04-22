#pragma once
#include "Entity.h"
#include "System.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include <unordered_map>
using namespace std;

class Manager {
private:
	array<vector<Entity*>, maxGroupId> entsByGroup_;
	array<System*, maxSystemId> sys_;
	array<Entity*, maxHandlerId> hdlrs_;

	vector<Message> msgs_;
	vector<Message> aux_msgs_;
	
public:
	// Mapa de textos asignados con un puntero a una textura
	unordered_map<Entity*, Texture*> UITextures_;

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

		for (auto it = UITextures_.begin(); it != UITextures_.end(); ++it) {
			delete UITextures_[it->first];
		}
	}
	// Actualiza todas las entidades
	virtual void update() {
		for (auto& sys : sys_) {
			if (sys != nullptr) {
				sys->update();
			}
		}

		flushMessages();
	}
	// Borra entidades no vivas de la escena
	void refresh() {

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
	// Anade una entidad al grupo
	template<typename T>
	Entity* addEntity(T* e, grpId_type gId = _grp_GENERAL) {
		e->setAlive(true);
		e->setContext(this);
		entsByGroup_[gId].push_back(e);
		return e;
	}
	// Devuelve el vector de entidades por grupo
	inline const auto& getEntities(grpId_type gId = _grp_GENERAL) {
		return entsByGroup_[gId];
	}
	// Anade un componente a la entidad
	template<typename T, typename ...Ts>
	inline T* addComponent(Entity* e, Ts&&...args) {
		T* c = new T(std::forward<Ts>(args)...);

		constexpr cmpId_type cId = T::id;
		removeComponent<T>(e);
		e->currCmps_.push_back(c);
		e->cmps_[cId] = c;

		e->setContext(this);
		e->initComponent();

		return c;
	}
	// Quita un componente de la entidad
	template<typename T>
	inline void removeComponent(Entity* e) {
		constexpr cmpId_type cId = T::id;
		if (e->cmps_[cId] != nullptr) {
			auto iter = std::find(e->currCmps_.begin(), e->currCmps_.end(), e->cmps_[cId]);
			e->currCmps_.erase(iter);
			delete e->cmps_[cId];
			e->cmps_[cId] = nullptr;
		}
	}
	// Devuelve si la entidad tiene o no el componente
	template<typename T>
	inline bool hasComponent(Entity* e) {
		constexpr cmpId_type cId = T::id;
		return e->cmps_[cId] != nullptr;
	}
	// Devuelve puntero al componente de la entidad
	template<typename T>
	inline T* getComponent(Entity* e) {
		constexpr cmpId_type cId = T::id;
		return static_cast<T*>(e->cmps_[cId]);
	}
	// Establece si la entidad esta vivo o no
	inline void setAlive(Entity* e, bool alive) {
		e->alive_ = alive;
	}
	// Devuelve si la entidad esta vivo o no
	inline bool isAlive(Entity* e) {
		return e->alive_;
	}
	// Devuelve el grupo al que pertenece la entidad
	inline grpId_type groupId(Entity* e) {
		return e->gId_;
	}
	// Anade un sistema al grupo
	template<typename T, typename ...Ts>
	inline T* addSystem(Ts &&... args) {
		constexpr sysId_type sId = T::id;
		removeSystem<T>();
		System* s = new T(std::forward<Ts>(args)...);
		s->setContext(this);
		s->initSystem();
		sys_[sId] = s;
		return static_cast<T*>(s);
	}
	// Devuelve el puntero al sistema
	template<typename T>
	inline T* getSystem() {
		constexpr sysId_type sId = T::id;
		return static_cast<T*>(sys_[sId]);
	}
	// Quita el sistema del grupo 
	template<typename T>
	inline void removeSystem() {
		constexpr sysId_type sId = T::id;
		if (sys_[sId] != nullptr) {
			delete sys_[sId];
			sys_[sId] = nullptr;
		}
	}
	// Establece la entidad como handler
	inline void setHandler(hdlrId_type hId, Entity* e) {}
	// Devuelve la entidad handler
	inline Entity* getHandler(hdlrId_type hId) {}

	// Envia mensaje con o sin delay
	inline void send(const Message& m, bool delay = false) {
		if (!delay) {
			for (System* s : sys_) {
				if (s != nullptr) {
					s->receive(m);
				}
			}
		}
		else {
			msgs_.emplace_back(m);
		}
	}
	// Borra los mensajes
	inline void flushMessages() {
		swap(msgs_, aux_msgs_);
		for (auto& m : aux_msgs_) {
			for (System* s : sys_) {
				if (s != nullptr)
					s->receive(m);
			}
		}
		aux_msgs_.clear();
	}
};