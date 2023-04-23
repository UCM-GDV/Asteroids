#pragma once
#include "../ecs/System.h"
#include "../utils/Collisions.h"

class CollisionsSystem : public System {
public:
	// Identificador
	constexpr static sysId_type id = _sys_COLLISIONS;

	// Constructora
	CollisionsSystem(int state_ = 1);
	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void receive(const Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;
	// Si el juego está parado no hacer nada, en otro caso comprobar colisiones como
	// en la práctica 1 y enviar mensajes correspondientes.
	virtual void update() override;
private:
	// Fighter
	Transform* fighterTransform;
	// Colisiones
	Collisions* col;
	// Estado actual del juego
	int state;
	Message m;
	// Detecta las colisiones dependendiendo del grupo de asteroide
	void collision(vector<Entity*> v);
	// Detecta las colisiones dependendiendo del grupo de asteroide
	void collisionNet(vector<Entity*> v);
	// Devuelve siha colisionado dos entidades dadas
	bool collisionEntities(Transform* Trans, Transform* Trans2);
};