#pragma once
#include "../ecs/System.h"
#include "../systems/FighterSystem.h"
#include "../components/Transform.h"
#include "../components/fighterComponents/Health.h"
#include "../components/asteroidsComponents/FramedImage.h"

class RenderSystem : public System {
public:
	// Identificador
	constexpr static sysId_type id = _sys_RENDER;

	// Constructora
	RenderSystem();
	RenderSystem(int state_);
	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void receive(const Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;
	// - Dibujar asteroides, balas y caza (sólo si el juego no está parado).
	// - Dibujar las vidas (siempre).
	// - Dibujar los mensajes correspondientes: si el juego está parado, etc (como en
	// la práctica 1)
	void update() override;

private:
	// Estado actual del juego
	int state;
	Uint8 winner_; // 0 - None, 1 - Asteroid, 2 - Fighter
	// Fighter
	Transform* fighterTransform;
	Health* fighterHealth;
	// Asteroids
	Transform* asteroidTrasform;
	FramedImage* asteroidFramedImage;
	// Balas
	Transform* bulletTransform;

	SDL_Rect dest;
	SDL_Rect src;
	int fw, fh, numCols, numRows, currentframe;

	Entity* text;
	Transform* textTransform;
	// FRAMEDIMAGE
	void renderAsteroid(Entity* a, Texture* tex);

	// ESTO DE AQUI NO LO VAMOS A USAR PORQUE TENEMOS MAQUINA DE ESTADOS
	// Para gestionar los mensajes correspondientes y actualizar los atributos
	// winner_ y state_. 
	//void onRoundStart();
	//void onRoundOver();
	//void onGameStart();
	//void onGameOver();
	
};