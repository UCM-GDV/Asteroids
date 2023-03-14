#pragma once
#include "../ecs/System.h"
class CollisionsSystem : public System {
public:
	// Identificador
	constexpr static sysId_type id = _sys_COLLISIONS;

	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void receive(const Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;
	// Si el juego está parado no hacer nada, en otro caso comprobar colisiones como
	// en la práctica 1 y enviar mensajes correspondientes.
	void update() override;
private:
	

	// Devuelve si algun asteroide ha colisionado con el fighter
	bool fighterCollision(Transform* asteroidTransform);
	// Devuelve si la bala ha colisionado con algun asteroide
	bool bulletCollision(Transform* bulletTransform, Transform* asteroidTransform);
	
	PlayState* mngr;
	Transform* fighterTransform;
	Health* fighterHealth;
	Collisions* col;

	// ESTO DE AQUI NO LO VAMOS A USAR PORQUE TENEMOS MAQUINA DE ESTADOS
	// Para gestionar el mensaje de que ha acabado una ronda. Desactivar el sistema.
	void onRoundOver();
	// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
	void onRoundStart();
	// Indica si el sistema está activo o no (modificar el valor en onRoundOver y
	// onRoundStart, y en update no hacer nada si no está activo)
	bool active_;
};