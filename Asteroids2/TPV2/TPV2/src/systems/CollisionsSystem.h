#pragma once
#include "../ecs/System.h"
#include "../utils/Collisions.h"

class CollisionsSystem : public System {
public:
	// Identificador
	constexpr static sysId_type id = _sys_COLLISIONS;

	// Constructora
	CollisionsSystem(int state_ = 1);
	// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
	void receive(const Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;
	// Si el juego est� parado no hacer nada, en otro caso comprobar colisiones como
	// en la pr�ctica 1 y enviar mensajes correspondientes.
	virtual void update() override;
private:
	// Fighter
	Transform* fighterTransform;
	// Colisiones
	Collisions* col;
	// Estado actual del juego
	int state;
	// Detecta las colisiones dependendiendo del grupo de asteroide
	void collision(vector<Entity*> v);
	// Devuelve si algun asteroide ha colisionado con el fighter
	bool fighterCollision(Transform* asteroidTransform);
	// Devuelve si la bala ha colisionado con algun asteroide
	bool bulletCollision(Transform* bulletTransform, Transform* asteroidTransform);
};