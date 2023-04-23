#pragma once
#include "../ecs/System.h"
#include "../sdlutils/SDLUtils.h"
#include <SDL_net.h>
#include "../components/Messagenet.h"
class PlayStateMultiPlayer;
class NetworkSystem : public System {
public:
	// Idenficador
	constexpr static sysId_type id = _sys_NETWORK;
	// Constructora
	NetworkSystem();
	~NetworkSystem();
	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void receive(const Message& m) override;
	// Crear la entidad del caza, añadir sus componentes, asociarla con un handler
	// correspondiente, etc.
	void initSystem() override;

	void update() override;

	// Servidor
	void server();
	// Cliente 
	void client(const char* host);
	bool getServer() {
		return server_;
	}

	void fighterUpdate(Vector2D pos, Vector2D vel, double width, double height, float rot);
	void addBullet(Vector2D pos, Vector2D vel, float rot);
	
private:
	UDPpacket* p;
	UDPsocket sd;
	SDLNet_SocketSet socketSet;
	Messagenet* mn;
	Message m;
	IPaddress srvadd; //direcion ip	IPaddress srvadd; //direcion ip
	bool server_;
	PlayStateMultiPlayer* playState;
};