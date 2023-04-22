#pragma once
#include "../ecs/System.h"
#include "../components/Transform.h"
#include "FighterSystem.h"
#include "../sdlutils/SDLUtils.h"

// Sistema responsable de las balas(crearlas, destruirlas, etc.).
class BulletSystem : public System {
public:
	// Identificador
    constexpr static sysId_type id = _sys_BULLET;

    // Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
    void receive(const Message& m) override;
    // Inicializar el sistema, etc.
    void initSystem() override;
    // Si el juego está parado no hacer nada, en otro caso mover las balas y
    // desactivar las que salen de la ventana como en la práctica 1.
    virtual void update() override;
private:
    // Fighter
   // Transform* fighterTransform;
    // Para gestionar el mensaje de que el jugador ha disparado. Añadir una bala al
    // juego, como en la práctica 1. Recuerda que la rotación de la bala sería
    // vel.angle(Vector2D(0.0f,-1.0f))
    void shoot(Vector2D pos, Vector2D vel, double width, double height, float rot);
    // Para gestionar el mensaje de que ha habido un choque entre una bala y un
    // asteroide. Desactivar la bala “b”.
    void onCollision_BulletAsteroid(Entity* b);
    // Destruye todas las balas de la escena
    void destroyAllBullets();
    // Para gestionar el mensaje de que ha acabado la ronda. Desactivar todas las
    // balas, y desactivar el sistema.
    void onRoundOver();
};
