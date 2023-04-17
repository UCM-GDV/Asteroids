// Yi (Laura) Wang Qiu & Cristina Mora Velasco (Grupo 20)

//#include <iostream>
//#include "game/Game.h"
//#include "utils/checkML.h"
//
//int main(int ac, char **av) {
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//
//	Game* game = nullptr;
//	try {
//		game = new Game();
//		game->run();
//	} catch (const std::string &e) {
//		std::cerr << e << std::endl;
//	} catch (const char *e) {
//		std::cerr << e << std::endl;
//	} catch (const std::exception &e) {
//		std::cerr << e.what();
//	} catch (...) {
//		std::cerr << "Caught and exception of unknown type ...";
//	}
//	delete game;
//
//	return 0;
//}

#include <SDL.h>
#include <SDL_net.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include "game/constants.h"

using namespace std;

void server(int port) {
    // abre un puerto cualquiera (via de mensajes)
	UDPsocket sd = SDLNet_UDP_Open(port);
    // si no consigue abrir
	if (!sd) {
        //error(); 
    }

    // creacion de un packet (estructura de datos a enviar/recibir)
	UDPpacket* p = SDLNet_AllocPacket(MAX_PACKET_SIZE); 
    // si no consigue crear
	if (!p) { 
        //error(); 
    }

	char* buffer = reinterpret_cast<char*>(p->data);
	SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(1);
	SDLNet_UDP_AddSocket(socketSet, sd);

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

    //libera 
	SDLNet_FreePacket(p); 
	SDLNet_FreeSocketSet(socketSet);
	SDLNet_UDP_Close(sd);
}

// conectar
void client(char* host, int port) {
    // coge el socket abierto 
	UDPsocket sd = SDLNet_UDP_Open(0);
	IPaddress srvadd; //direcion ip
	if (SDLNet_ResolveHost(&srvadd, host, port) < 0) { 
        //error(); 
    }
	UDPpacket* p = SDLNet_AllocPacket(MAX_PACKET_SIZE);
	char* buffer = reinterpret_cast<char*>(p->data);
	SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(1);
	SDLNet_UDP_AddSocket(socketSet, sd);
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
	SDLNet_FreePacket(p);
	SDLNet_FreeSocketSet(socketSet);
	SDLNet_UDP_Close(sd);
}


int main(int argc, char** argv) {
    if (SDL_Init(0) == -1) {
        printf("SDL_Init: %s\n", SDL_GetError());
        exit(1);
    }
    if (SDLNet_Init() == -1) {
        printf("SDLNet_Init: %s\n", SDLNet_GetError());
        exit(2);
    }

    bool done = false;
    if (argc == 2 && strcmp(argv[1], "server") == 0) {
        printf("Starting server...\n");

        server(PORT);
    }
    else if (argc == 2 && strcmp(argv[1], "client") == 0) {
        printf("Starting client...\n");

        // le pide la direccion IP a conectarse
        printf("IP: ");
        char host[1024];
        fgets(host, 1024, stdin);
        client(host, PORT);
    }
    else {
        printf("Choose server or client\n");
    }

    SDLNet_Quit();
    SDL_Quit();
}


