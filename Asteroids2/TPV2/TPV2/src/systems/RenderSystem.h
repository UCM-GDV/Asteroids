#pragma once
#include "../ecs/System.h"
#include "../components/fighterComponents/Health.h"

#include "../ecs/Manager.h"
class RenderSystem : public System {
public:
	// Identificador
	constexpr static sysId_type id = _sys_RENDER;

	// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
	void receive(const Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;
	// - Dibujar asteroides, balas y caza (s�lo si el juego no est� parado).
	// - Dibujar las vidas (siempre).
	// - Dibujar los mensajes correspondientes: si el juego est� parado, etc (como en
	// la pr�ctica 1)
	void update() override;
private:
//	Transform* fighterTransform;
	//Health* fighterHealth;
	
	// ESTO DE AQUI NO LO VAMOS A USAR PORQUE TENEMOS MAQUINA DE ESTADOS
	// Para gestionar los mensajes correspondientes y actualizar los atributos
	// winner_ y state_. 
	//void onRoundStart();
	//void onRoundOver();
	//void onGameStart();
	//void onGameOver();
	//Uint8 winner_; // 0 - None, 1 - Asteroid, 2 - Fighter
	//Uint8 state_; // El estado actual de juego (como en GameCtrlSystem)
};