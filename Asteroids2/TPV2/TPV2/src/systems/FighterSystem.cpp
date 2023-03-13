#include "FighterSystem.h"
// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
void FighterSystem::receive(const Message& m) {

}
// Crear la entidad del caza, a�adir sus componentes, asociarla con un handler
// correspondiente, etc.
void FighterSystem::initSystem() {}
// Si el juego est� parado no hacer nada, en otro caso actualizar la velocidad
// del caza y moverlo como en la pr�ctica 1 (acelerar, desacelerar, etc). Adem�s, 
// si el juego no est� parado y el jugador pulsa la tecla de disparo, enviar un
// mensaje con las caracter�sticas f�sicas de la bala. Recuerda que se puede disparar
// s�lo una bala cada 0.25sec.
void FighterSystem::update() {}
// Para reaccionar al mensaje de que ha habido un choque entre el fighter y un
// un asteroide. Poner el caza en el centro con velocidad (0,0) y rotaci�n 0. No
// hace falta desactivar la entidad (no dibujarla si el juego est� parado).
void FighterSystem::onCollision_FighterAsteroid(){}
// Para gestionar el mensaje de que ha acabado una ronda. Desactivar el sistema.
void FighterSystem::onRoundOver(){}
// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
void FighterSystem::onRoundStart(){}