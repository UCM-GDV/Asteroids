#include "BulletSystem.h"

    // Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void BulletsSystem::receive(const Message& m) {
}
    // Inicializar el sistema, etc.
void BulletsSystem::initSystem() {

}
    // Si el juego está parado no hacer nada, en otro caso mover las balas y
    // desactivar las que salen de la ventana como en la práctica 1.
    void BulletsSystem::update() {
    }
    // Para gestionar el mensaje de que el jugador ha disparado. Añadir una bala al
    // juego, como en la práctica 1. Recuerda que la rotación de la bala sería
    // vel.angle(Vector2D(0.0f,-1.0f))
    void BulletsSystem::shoot(Vector2D pos, Vector2D vel, double width, double height) {
    }
    // Para gestionar el mensaje de que ha habido un choque entre una bala y un
    // asteroide. Desactivar la bala “b”.
    void BulletsSystem::onCollision_BulletAsteroid(Entity* b) {

    }
    // Para gestionar el mensaje de que ha acabado la ronda. Desactivar todas las
    // balas, y desactivar el sistema.
    void BulletsSystem::onRoundOver() {

    }
    // Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
    void BulletsSystem::onRoundStart() {

    }

