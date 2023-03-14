#pragma once
#include "../ecs/System.h"
#include "../components/fighterComponents/Gun.h"

//Sistema responsable de las balas(crearlas, destruirlas, etc.).
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
    void update() override;
private:
    // Para gestionar el mensaje de que el jugador ha disparado. Añadir una bala al
    // juego, como en la práctica 1. Recuerda que la rotación de la bala sería
    // vel.angle(Vector2D(0.0f,-1.0f))
    void shoot(Vector2D pos, Vector2D vel, double width, double height);
    // Para gestionar el mensaje de que ha habido un choque entre una bala y un
    // asteroide. Desactivar la bala “b”.
    void onCollision_BulletAsteroid(Entity* b);
    // Destruye todas las balas de la escena
    void destroyAllBullets();
    // Puntero al gun del fighter
    Gun* fighterGun;

    // ESTO DE AQUI NO LO VAMOS A USAR PORQUE TENEMOS MAQUINA DE ESTADOS
    // Para gestionar el mensaje de que ha acabado la ronda. Desactivar todas las
    // balas, y desactivar el sistema.
    //void onRoundOver();
    //// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
    //void onRoundStart();
    //// Indica si el sistema está activo o no (modificar el valor en onRoundOver y
    //// onRoundStart, y en update no hacer nada si no está activo)
    //bool active_;
};
