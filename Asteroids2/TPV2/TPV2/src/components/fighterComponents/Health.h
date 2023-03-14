#pragma once 
#include "../../ecs/Component.h"
#include "../../sdlutils/Texture.h"
#include "../../sdlutils/SDLUtils.h"

struct Health : public Component {
private:
	int lives;
	Texture* texture;
public:
    // Identificador
    constexpr static cmpId_type id = _HEALTH;
	// Constructora
	Health();
	// Destructora
    virtual ~Health();
	// Inicializa el componente
	void initComponent();
	// Renderiza las vidas
	void render();
	// Devuelve el numero de vidas actual
	inline int getLives() { return lives; }
	// Establece el numero de vidas actual
	inline void setLives(int lives_) { lives = lives_; }
	// Decrementa el numero de vidas actual
	inline void decreaseLive() { --lives; }
	// Reestable el numero de vidas actual
	inline void resetLives() { lives = NUMBER_LIVES; }
};
