#pragma once
#ifndef MANAGER_H_
#define MANAGER_H_
#include <vector>
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
	void render() {
		auto n = ents_.size();
		for (auto i = 0u; i < n; i++)
			ents_[i]->render();
	}
	// Manejo de los eventos de todas las entidades
	/*void handleEvent(SDL_Event event) {
		auto n = ents_.size();
		for (auto i = 0u; i < n; i++)
			ents_[i]->handleEvent(event);
	}*/
private:
	vector<Entity*> ents_;
};
#endif