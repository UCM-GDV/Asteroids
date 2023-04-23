#include "NetWorkSystem.h"
#include "../ecs/Manager.h"
#include "../states/PlayStateMultiplayer.h"
#include <string>
using namespace std;
// Constructora
NetworkSystem::NetworkSystem() {
	if (SDLNet_Init() < 0) {
		throw SDLNet_GetError();
	}
}

// Destructora
NetworkSystem::~NetworkSystem() {
	SDLNet_FreePacket(p);
	SDLNet_FreeSocketSet(socketSet);
	SDLNet_UDP_Close(sd);
}

// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void NetworkSystem::receive(const Message& m) {
	switch (m.id) {
	case _m_FIGHTER_UPDATE: fighterUpdate(m.fighter_update.pos, m.fighter_update.vel, m.fighter_update.width, m.fighter_update.height,m.fighter_update.rot); break;
	case _m_ADD_BULLET: addBullet(m.add_bullet.pos, m.add_bullet.vel, m.add_bullet.rot); break;
	case _m_DISCONNECT: disconnect(); break;
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

	mn = reinterpret_cast<Messagenet*>(p->data);
	mn->id = _m_CONNECTED;
	p->len = sizeof(Messagenet);
	p->address = srvadd;
	socketSet = SDLNet_AllocSocketSet(1);
	SDLNet_UDP_AddSocket(socketSet, sd);
}

// Conecta con el host y el puerto
void NetworkSystem::client(const char* host) {
	server_ = false;

	// coge el socket abierto 
	sd = SDLNet_UDP_Open(0);
	string ip = static_cast<PlayStateMultiPlayer*>(mngr_)->getIp();
	//if (SDLNet_ResolveHost(&srvadd, ip.c_str(), PORT) < 0) {
		if (SDLNet_ResolveHost(&srvadd, "192.168.1.134", PORT) < 0) {
		throw("ERROR AL ESTABLECER CONEXION CON EL SERVIDOR");
	}
	p = SDLNet_AllocPacket(MAX_PACKET_SIZE);
	socketSet = SDLNet_AllocSocketSet(1);
	SDLNet_UDP_AddSocket(socketSet, sd);
	
	mn = reinterpret_cast<Messagenet*>(p->data);
	mn->id = _m_CONNECTED;
	p->len = sizeof(Messagenet);
	p->address = srvadd;
	SDLNet_UDP_Send(sd, -1, p);
	//cambio de estado
}

void NetworkSystem::initSystem() {
}

void NetworkSystem::update() {
	
	// Si recibe algun mensaje
	if (SDLNet_UDP_Recv(sd, p) > 0) {
		switch (mn->id) {
		case _m_CONNECTED:
			playState = static_cast<PlayStateMultiPlayer*>(mngr_);
			if (server_) {
				cout << "connected";
				srvadd = p->address;
				// Quita el texto de espera
				playState->getWaitingText()->setAlive(false);

				// Envia un mensaje de que se ha conectado el servidor
				mn->id = _m_CONNECTED;
				p->len = sizeof(Messagenet);
				p->address = srvadd;
				SDLNet_UDP_Send(sd, -1, p);
			}
			// Anade los sistemas necesarios para el multijugador
			playState->createsystems();
			// Cambia del modo de seleccion al juego multijugador
			m.id = _m_CHANGE_STATE;
			mngr_->send(m);
			break;
		case _m_FIGHTERPOSUP:
			//llama a fightersystem para que actualize la pos y rot 1  o 2
			//manda un mensaje normal para que actualice la pos
			m.id = _m_NET_FIGHTER_UPDATE;
			m.fighterposup.pos = mn->fighter_update.pos;
			m.fighterposup.vel = mn->fighter_update.vel;
			m.fighterposup.width = mn->fighter_update.width;
			m.fighterposup.height = mn->fighter_update.height;
			m.fighterposup.rot = mn->fighter_update.rot;
			mngr_->send(m);
			break;
		case _m_ADDBULLET:
			//para crear la bala cog pos, rot y vel y la crea
			m.id = _m_NET_ADD_BULLET;
			m.add_bullet.pos = mn->add_bullet.pos;
			m.add_bullet.vel = mn->add_bullet.vel;
			m.add_bullet.rot = mn->add_bullet.rot;
			mngr_->send(m);
			break;
		case _m_NAME:
			//se le pasa el nombre al otro usuario
			othername = string(mn->name);
			static_cast<PlayStateMultiPlayer*>(mngr_)->addName(othername);
			break;
		case _m_DISCONNECTED: 
			cout << "se desconecta" << endl;
			m.id = _m_RESET_MULTIPLAYER_STATE;
			mngr_->send(m);
			break;
		default: break;
		}
	}
	//else if (mngr_->getSystem<FighterSystem>()!= NULL) {
	//	Message m;
	//	m.id = _m_RESET_MULTIPLAYER_STATE;
	//	mngr_->send(m);
	//}
}
void NetworkSystem::sendname(string name) {
	mn->id = _m_NAME;
	strcpy_s(mn->name, name.c_str());
	p->len = sizeof(Messagenet);
	p->address = srvadd;
	SDLNet_UDP_Send(sd, -1, p);
}
void NetworkSystem::fighterUpdate(Vector2D pos, Vector2D vel, double width, double height, float rot) {
	mn->id = _m_FIGHTERPOSUP;
	mn->fighter_update.pos = pos;
	mn->fighter_update.vel = vel;
	mn->fighter_update.width = width;
	mn->fighter_update.height = height;
	mn->fighter_update.rot = rot;
	p->len = sizeof(Messagenet);
	p->address = srvadd;
	SDLNet_UDP_Send(sd, -1, p);
}

void NetworkSystem::addBullet(Vector2D pos, Vector2D vel, float rot) {
	// Anade una bala en el programa del otro
	mn->id = _m_ADDBULLET;
	mn->add_bullet.pos = pos;
	mn->add_bullet.vel = vel;
	mn->add_bullet.rot = rot;
	p->len = sizeof(Messagenet);
	p->address = srvadd;
	SDLNet_UDP_Send(sd, -1, p);

	//reproduce el sonido de disparo del otro jugador
	SDLUtils::instance()->soundEffects().at("fire").play();
}

void NetworkSystem::disconnect() {
	mn->id = _m_DISCONNECTED;
	p->len = sizeof(Messagenet);
	p->address = srvadd;
	SDLNet_UDP_Send(sd, -1, p);

	cout << "se envia el mensaje" << endl;
}