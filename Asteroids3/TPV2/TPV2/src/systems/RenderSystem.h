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

	// Constructoras
	RenderSystem();
	RenderSystem(int state_);
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
	// Estado actual del juego
	int state;
	// Fighter
	Transform* fighterTransform;
	Health* fighterHealth;
	// Asteroids
	Transform* asteroidTrasform;
	FramedImage* asteroidFramedImage;
	// Balas
	Transform* bulletTransform;
	// Texto
	Entity* text;
	Transform* textTransform;

	// FRAMEDIMAGE
	SDL_Rect dest;
	SDL_Rect src;
	int fw, fh, numCols, numRows, currentframe;
	void renderAsteroid(Entity* a, Texture* tex);
};