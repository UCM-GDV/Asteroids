#include "NetWorkSystem.h"
#include "../ecs/Manager.h"

// Constructora
NetworkSystem::NetworkSystem() {
	if (SDLNet_Init() < 0) {
		throw SDLNet_GetError();
	}
}
NetworkSystem::~NetworkSystem() {
	SDLNet_FreePacket(p);
	SDLNet_FreeSocketSet(socketSet);
	SDLNet_UDP_Close(sd);
}

// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void NetworkSystem::receive(const Message& m) {
    switch (m.id) {
        case _m_ROUND_FINISHED: break;
		case _m_ONVICTORY: case _m_ONDEFEAT: break;
		//case _m_ROTATE: if (server_) {
		//	// Llamar a un metodo que haga SDLNet_UDP_Send
		//	// al cliente para que actualice la rotacion
		//	// del fighterTransform2
		//}
		//else {
		//	// Llamar un metodo que haga SDLNet_UDP_Send 
		//	// al servidor para que actualice la rotacion
		//	// del fighterTransform1
		//}
		//case _m_ACCELERATE: if (server_) {
		//	// Llamar a un metodo que haga SDLNet_UDP_Send
		//	// al cliente para que actualice la posicion
		//	// del fighterTransform2
		//}
		//else {
		//	// Llamar a un metodo que haga SDLNet_UDP_Send
		//	// al cliente para que actualice la posicion
		//	// del fighterTransform2
		//}
        default: break;
    }
}

// Crea servidor
void NetworkSystem::server() {
	server_ = true;

	// abre un puerto cualquiera (via de mensajes)
	sd = SDLNet_UDP_Open(PORT);
	// si no consigue abrir
	if (!sd) {
		throw("ERROR AL ABRIR EL SERVER");
	}

	// creacion de un packet (estructura de datos a enviar/recibir)
	p = SDLNet_AllocPacket(MAX_PACKET_SIZE);
	// si no consigue crear
	if (!p) {
		throw("ERROR AL CREAR EL PAQUETE");
	}

	char* buffer = reinterpret_cast<char*>(p->data);
	socketSet = SDLNet_AllocSocketSet(1);
	SDLNet_UDP_AddSocket(socketSet, sd);
}

// Conecta con el host y el puerto
void NetworkSystem::client(const char* host) {
	server_ = false;

	// coge el socket abierto 
	sd = SDLNet_UDP_Open(0);

	if (SDLNet_ResolveHost(&srvadd, "192.168.252.63", PORT) < 0) {
		//if (SDLNet_ResolveHost(&srvadd, host, port) < 0) {
		throw("ERROR AL ESTABLECER CONEXION CON EL SERVIDOR");
	}
	p = SDLNet_AllocPacket(MAX_PACKET_SIZE);
	socketSet = SDLNet_AllocSocketSet(1);
	SDLNet_UDP_AddSocket(socketSet, sd);
	
	m = reinterpret_cast<Messagenet*>(p->data);
	m->id = _m_CONNECTED;
	p->len = sizeof(Messagenet);
	p->address = srvadd;
	SDLNet_UDP_Send(sd, -1, p);
}

void NetworkSystem::initSystem() {
	
}

void NetworkSystem::update() {
	
	// Esto se encarga de recibir todos los mensajes
	if (SDLNet_UDP_Recv(sd, p) > 0) {
		switch (m->id) {
		case _m_CONNECTED: if (server_) { srvadd = p->address; } break;
		default: break;
		}
	}
}
