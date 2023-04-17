#include "MainMenuState.h"

// Constructora
MainMenuState::MainMenuState() {
	fighterSys_ = addSystem<FighterSystem>(-1);
	gameCtrlSys_ = addSystem<GameCtrlSystem>(-1);
	renderSys_ = addSystem<RenderSystem>(-1);

	// Crear botones para el modo de un jugador y modo multijugador
	// En el RenderSystem, dibujar los botones
	// En el GameCtrlSystem, gestionar el click del boton

	// Idea de Laura:
	// Al clicar sobre el boton de multijugador, aparezca:
	// Opcion de server
	// Opcíon de cliente

	// Al clicar en cualquiera de las anteriores opciones, pregunta por
	// el nombre (sera el que se renderizará encima de las cazas)
	// => Hacer cambios en el RenderSystem para eso

	// En la opción de server aparecerá el texto de "Waiting for other player...",
	// que desaparecerá hasta que el otro jugador se haya conectado

	// En la opción de cliente aparecerá un cuadro de texto para que introducir
	// la IP del host


	if (SDL_Init(0) == -1) {
		printf("SDL_Init: %s\n", SDL_GetError());
		exit(1);
	}
	if (SDLNet_Init() == -1) {
		printf("SDLNet_Init: %s\n", SDLNet_GetError());
		exit(2);
	}

	cout << "1 para server\n2 para cliente" << endl;
	string a;
	cin >> a;

	if (a == "1") server(PORT);
	else {
		// Pregunta por la IP
		cout << "IP: ";
		char host[1024];
		cin >> host;
		client(host, PORT);
	}
}

// Destructora
MainMenuState::~MainMenuState() {
	SDLNet_Quit();
	SDL_Quit();
}

// Crea servidor
void MainMenuState::server(int port) {
	// abre un puerto cualquiera (via de mensajes)
	UDPsocket sd = SDLNet_UDP_Open(port);
	// si no consigue abrir
	if (!sd) {
		throw("ERROR AL ABRIR EL SERVER");
		//error(); 
	}

	// creacion de un packet (estructura de datos a enviar/recibir)
	UDPpacket* p = SDLNet_AllocPacket(MAX_PACKET_SIZE);
	// si no consigue crear
	if (!p) {
		throw("ERROR AL CREAR EL PAQUETE");
		//error(); 
	}

	char* buffer = reinterpret_cast<char*>(p->data);
	SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(1);
	SDLNet_UDP_AddSocket(socketSet, sd);

	// MODIFICAR ESTE CODIGO PARA QUE SEA NUESTRO JUEGO

	bool end = false;

	while (!end) {
		// TODO I: PROCESS DATA on socket sd
		//actividad en clientes
		if (SDLNet_CheckSockets(socketSet, SDL_MAX_UINT32) > 0) {
			if (SDLNet_SocketReady(sd)) {
				if (SDLNet_UDP_Recv(sd, p) > 0) {
					// print client’s message
					cout << "Client says: " << buffer << endl;
					// send a response
					memcpy(buffer, "Received!", 10);
					p->len = 10;
					SDLNet_UDP_Send(sd, -1, p);
				}
			}
		}
	}

	// ESTO DE AQUI DEBE LLAMARSE EN LA DESTRUCTORA DEL JUEGO
	// libera 
	SDLNet_FreePacket(p);
	SDLNet_FreeSocketSet(socketSet);
	SDLNet_UDP_Close(sd);
}

// Conecta con el host y el puerto
void MainMenuState::client(char* host, int port) {
    // coge el socket abierto 
	UDPsocket sd = SDLNet_UDP_Open(0);
	IPaddress srvadd; //direcion ip
	if (SDLNet_ResolveHost(&srvadd, host, port) < 0) { 
		throw("ERROR AL ESTABLECER CONEXION CON EL SERVIDOR");
        //error(); 
    }
	UDPpacket* p = SDLNet_AllocPacket(MAX_PACKET_SIZE);
	char* buffer = reinterpret_cast<char*>(p->data);
	SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(1);
	SDLNet_UDP_AddSocket(socketSet, sd);

	// MODIFICAR ESTE CODIGO PARA QUE SEA NUESTRO JUEGO
	while (1) {
		// TODO I: PROCESS DATA on socket sd
		cout << "Enter a message: ";
		cin.getline(buffer, 255);
		if (strcmp(buffer, "exit") == 0) { break; }
		p->len = static_cast<int>(strlen(buffer)) + 1;
		p->address = srvadd;
		SDLNet_UDP_Send(sd, -1, p);
		if (SDLNet_CheckSockets(socketSet, 3000) > 0) {
			if (SDLNet_SocketReady(sd)) {
				while (SDLNet_UDP_Recv(sd, p) > 0) {
					cout << "Server says: " << buffer << endl;
				}
			}
		}
	}

	// ESTO DE AQUI DEBE LLAMARSE EN LA DESTRUCTORA DEL JUEGO
	SDLNet_FreePacket(p);
	SDLNet_FreeSocketSet(socketSet);
	SDLNet_UDP_Close(sd);
}