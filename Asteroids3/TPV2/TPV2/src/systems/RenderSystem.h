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
	// Fighter
	Transform* fighterTransform;
	Health* fighterHealth;
	// Asteroids
	Transform* asteroidTrasform;
	FramedImage* asteroidFramedImage;
	// Balas
	Transform* bulletTransform;

	// Multiplayer
	Transform* fighterTransform1;
	Health* fighterHealth1;
	Transform* fighterTransform2;
	Health* fighterHealth2;
	// Texto
	Transform* auxTransform;

	// FRAMEDIMAGE
	SDL_Rect dest;
	SDL_Rect src;
	int fw, fh, numCols, numRows, currentframe;
	void renderAsteroid(Entity* a, string key);

	void renderFighter(Transform* tr, string key);
	void onChangeState();
	void renderLives(Health* health, Vector2D initialPos, string key);
	void renderBullet(Entity* b, string key);
	void renderUI(Entity* t);
	void renderUIname(Entity* t);
};