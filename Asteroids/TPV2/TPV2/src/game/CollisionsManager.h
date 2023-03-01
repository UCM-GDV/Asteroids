#pragma once
#include <cassert>
#include "../utils/Collisions.h"
#include "../components/Transform.h"
#include "../utils/Singleton.h"
class PlayState;

class CollisionsManager: public Singleton<CollisionsManager> {

	friend Singleton<CollisionsManager>; 
private:
	Collisions* col;
	PlayState* mngr;
	Transform* fighterTransform;
public:
	// Constructora
	CollisionsManager();
	// Inicializa
	void init(PlayState * m);
	// Destructora
	virtual ~CollisionsManager();
	// Comprueba las colisiones de todos los asteroides con el fighter y las balas
	void checkCollision();
	// Reestablece la posicion, velocidad y rotacion del fighter
	void resetFighter();
};