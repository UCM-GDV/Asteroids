#pragma once
#include "../ecs/System.h"
#include "../Components/Transform.h" 
#include "../Components/fighterComponents/Health.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

class NetworkSystem : public System {
public:
	// Identificador
	constexpr static sysId_type id = _sys_FIGHTER;

	// Constructora
	NetworkSystem(int state_ = 1);
	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void receive(const Message& m) override;
	// Crear la entidad del caza, añadir sus componentes, asociarla con un handler
	// correspondiente, etc.
	void initSystem() override;
	// Si el juego está parado no hacer nada, en otro caso actualizar la velocidad
	// del caza y moverlo como en la práctica 1 (acelerar, desacelerar, etc). Además, 
	// si el juego no está parado y el jugador pulsa la tecla de disparo, enviar un
	// mensaje con las características físicas de la bala. Recuerda que se puede disparar
	// sólo una bala cada 0.25sec.
	void update() override;
	// Devuelve el transform del fighter
	Transform* getFighterTransform();
	// Devuelve el health del fighter
	Health* getFighterHealth();

private:
	// Contador para las balas
	int startTime;
	// Estado actual del juego
	int state;
	// Punteros a elementos del fighter
	Entity* fighter;
	Transform* fighterTransform;
	Health* fighterHealth;

	// Para reaccionar al mensaje de que ha habido un choque entre el fighter y un
	// un asteroide. Poner el caza en el centro con velocidad (0,0) y rotación 0. No
	// hace falta desactivar la entidad (no dibujarla si el juego está parado).
	void onCollision_FighterAsteroid();
	// Para gestionar el mensaje de que ha acabado una ronda. Desactivar el sistema.
	void onRoundOver();

	// TRANSFORM - DEACCELERATION - SHOWATOPPOSITESIDE 
	void updatefighter();
	// Acelera al fighter
	void accelerate();
	// Rota el fighter
	void rotate(float r_);
	
	// Devuelve el numero de vidas
	inline int getLives() { return fighterHealth->getlife(); }
	// Decrementa el numero de vidas actual
	inline void decreaseLives() { fighterHealth->decreaseLives(); }
	// Resetea el numero de vidas actual
	inline void resetLives() { fighterHealth->setlife(NUMBER_LIVES); }

	// Reestablece la posicion, velocidad y rotacion del fighter
	inline void resetFighter() {
		fighterTransform->setPos({ WIN_HALF_WIDTH, WIN_HALF_HEIGHT });
		fighterTransform->setVel(FIGHTER_VELOCITY);
		fighterTransform->setRot(0);
	}

	// Pasa de grados a radianes
	inline float degreesToRadians(float degrees_) { return (degrees_ * (M_PI / 180)); }
};