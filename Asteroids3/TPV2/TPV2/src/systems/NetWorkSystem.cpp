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
	return;
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

	if (SDLNet_ResolveHost(&srvadd, "192.168.1.134", PORT) < 0) {
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
	//preguntar lo de la ip no?
}

void NetworkSystem::update() {
	
	// Esto se encarga de recibir todos los mensajes
	while  (SDLNet_UDP_Recv(sd, p) > 0) {
		switch (m->id) {
		case _m_CONNECTED: if (server_) { srvadd = p->address; } break;
		case _m_FIGHTERPOSUP:
			//llama a fightersystem para que actualize la pos y rot 1  o 2
			break;
		case _m_BULLETPOSUP:
			//para crear la bala cog pos, rot y vel y la crea
			break;

		default: break;
		}
	}
}
//mandar la pos del fighter con mensaje
//mandar la pos bala por mensaje
