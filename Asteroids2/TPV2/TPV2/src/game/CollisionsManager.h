//#pragma once
//#include <cassert>
//#include "../utils/Collisions.h"
//#include "../components/Transform.h"
//#include "../components/fighterComponents/Health.h"
//#include "../utils/Singleton.h"
//class PlayState;
//
//class CollisionsManager: public Singleton<CollisionsManager> {
//
//	friend Singleton<CollisionsManager>; 
//private:
//	PlayState* mngr;
//	Transform* fighterTransform;
//	Health* fighterHealth;
//    Collisions* col;
//public:
//	// Constructora
//	CollisionsManager();
//	// Inicializa
//	void init(PlayState * m);
//	// Destructora
//	virtual ~CollisionsManager();
//	// Comprueba las colisiones de todos los asteroides con el fighter y las balas
//	void checkCollision();
//	// Destruye todas las balas de la escena
//	void destroyAllBullets();
//	// Devuelve si algun asteroide ha colisionado con el fighter
//	bool fighterCollision(Transform* asteroidTransform);
//	// Devuelve si la bala ha colisionado con algun asteroide
//	bool bulletCollision(Transform* bulletTransform, Transform* asteroidTransform);
//	// Quita una vida, resetea y gestiona si se pausa o se finaliza el juego
//	void fighterOnCollision();
//	// Reestablece la posicion, velocidad y rotacion del fighter
//	void resetFighter();
//};