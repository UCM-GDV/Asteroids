#pragma once
#include "../ecs/System.h"
#include "../components/Transform.h"
#include "../states/PlayState.h"
#include "../ecs/Entity.h"

// Sistema responsable de los asteroides (crear, destruir, etc).
class AsteroidsSystem : public System {
public:
	constexpr static sysId_type id = _sys_ASTEROIDS;

	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void receive(const Message& m) override;
	// Inicializa el sistema
	void initSystem() override;
	// Si el juego está parado no hacer nada, en otro caso mover los asteroides como
	// en la práctica 1 y generar 1 asteroide nuevo cada 5 segundos (aparte
	// de los 10 al principio de cada ronda).
	virtual void update();
	// Destructora
	virtual ~AsteroidsSystem();
private:
	// Para gestionar el mensaje de que ha acabado la ronda. Desactivar todos los
	// asteroides, y desactivar el sistema.
	void onRoundOver();
	// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema y
	// añadir los asteroides iniciales (como en la práctica 1).
	void onRoundStart();
	// Crea n asteroides
	void createAsteroids(int n);
	// Reutiliza el metodo de createAsteroids para instanciar 1 asteroide cada cierto tiempo
	//void addAsteroidFrequently();
	// Destruye todos los asteroides pertenecientes al _grp_ASTEROIDS de las entidades de la escena
	void destroyAllAsteroids();
	// Para gestionar el mensaje de que ha habido un choque de un asteroide con una
	// bala. Desactivar el asteroide “a” y crear 2 asteroides como en la práctica 1,
	// y si no hay más asteroides enviar un mensaje correspondiente.
	void onCollision_AsteroidBullet(Entity* a);
	// Crea un asteroide blanco con sus componentes
	void createWhiteAsteroid(Vector2D pos, Vector2D vel, float width, float height, int g);
	// Crea un asteroide amarillo con sus componentes
	void createYellowAsteroid(Vector2D pos, Vector2D vel, float width, float height, int g);
	// Devuelve una posicion aleatoria
	Vector2D choosePosition(float width, float height);
	// Devuelve una velocidad aleatoria
	Vector2D chooseVelocity(Vector2D p);
	// El número actual de asteroides en el juego (recuerda que no puede superar un
	// límite)
	Uint8 numOfAsteroids_;
	// Indica si el sistema está activo o no (modificar el valor en onRoundOver y
	// onRoundStart, y en update no hacer nada si no está activo)
	bool active_;

	int startTime;
	PlayState* mngr;
	Entity* asteroid;
};
