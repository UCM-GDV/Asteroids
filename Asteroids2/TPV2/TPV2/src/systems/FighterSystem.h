#pragma once
#include <cassert>
#include "../ecs/System.h"
#include "../Components/Transform.h" 
#include "../Components/fighterComponents/Health.h"
#include "../Components/fighterComponents/Gun.h"
#include "../Components/fighterComponents/DeAcceleration.h"
#include "../Components/ShowAtOppositeSide.h"

class FighterSystem : public System {
public:
	// Identificador
	constexpr static sysId_type id = _sys_FIGHTER;

	// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
	void receive(const Message& m) override;
	// Crear la entidad del caza, a�adir sus componentes, asociarla con un handler
	// correspondiente, etc.
	void initSystem() override;
	// Si el juego est� parado no hacer nada, en otro caso actualizar la velocidad
	// del caza y moverlo como en la pr�ctica 1 (acelerar, desacelerar, etc). Adem�s, 
	// si el juego no est� parado y el jugador pulsa la tecla de disparo, enviar un
	// mensaje con las caracter�sticas f�sicas de la bala. Recuerda que se puede disparar
	// s�lo una bala cada 0.25sec.
	void update() override;
private:
	// Para reaccionar al mensaje de que ha habido un choque entre el fighter y un
	// un asteroide. Poner el caza en el centro con velocidad (0,0) y rotaci�n 0. No
	// hace falta desactivar la entidad (no dibujarla si el juego est� parado).
	void onCollision_FighterAsteroid();
	// Acelera al fighter
	void accelerate();
	// Reestablece la posicion, velocidad y rotacion del fighter
	inline void resetFighter() {
		fighterTransform->setPos({ WIN_HALF_WIDTH, WIN_HALF_HEIGHT });
		fighterTransform->setVel(FIGHTER_VELOCITY);
		fighterTransform->setRot(0);
	}
	// Devuelve el numero de vidas
	inline int getLives() { return fighterHealth->getLives(); }
	// Decrementa el numero de vidas actual
	inline void decreaseLives() { fighterHealth->decreaseLive(); }
	// Resetea el numero de vidas actual
	inline void resetLives() { fighterHealth->setLives(NUMBER_LIVES); }
	// Fighter
	Entity* fighter;
	Transform* fighterTransform;
	Health* fighterHealth;
	Gun* fighterGun;
	DeAcceleration* fighterDeAcceleration;
	ShowAtOppositeSide* fighterShowAtOppositeSide;
	
	void rotate(float r_);
	float degreesToRadians(float degrees_);
	// ESTO DE AQUI NO LO VAMOS A USAR PORQUE TENEMOS MAQUINA DE ESTADOS
	// Para gestionar el mensaje de que ha acabado una ronda. Desactivar el sistema.
	void onRoundOver();
	// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
	void onRoundStart();
	// Indica si el sistema est� activo o no (modificar el valor en onRoundOver y
	// onRoundStart, y en update no hacer nada si no est� activo)
	bool active_;
};