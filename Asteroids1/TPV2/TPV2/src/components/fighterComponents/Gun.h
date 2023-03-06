#pragma once
#include "../../ecs/Component.h"
#include "../Transform.h"
#include "../../ecs/Entity.h"
#include <cassert>
class PlayState;

class Gun : public Component {
private:
	Transform* transform;
	int startTime;
public:
	// Constructora
	Gun();
	// Destructora
	virtual ~Gun();
	// Inicializa el componente
	void initComponent();
    // Recoge el input del jugador
	void handleEvent(SDL_Event event);
    // Confirma que se trata de la escena de PlayState y anade una bala a la escena
	void tryShoot();
};