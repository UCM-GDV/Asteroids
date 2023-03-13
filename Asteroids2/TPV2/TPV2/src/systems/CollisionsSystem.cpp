#include "CollisionsSystem.h"
	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void CollisionsSystem::receive(const Message& m) {
	}
	// Inicializar el sistema, etc.
	void CollisionsSystem::initSystem() {}
	// Si el juego está parado no hacer nada, en otro caso comprobar colisiones como
	// en la práctica 1 y enviar mensajes correspondientes.
	void CollisionsSystem::update() {}
	// Para gestionar el mensaje de que ha acabado una ronda. Desactivar el sistema.
	void CollisionsSystem::onRoundOver() {}
	// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
	void CollisionsSystem::onRoundStart() {}
