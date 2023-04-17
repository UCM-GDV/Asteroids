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

//#include <SDL.h>
//#include <SDL_net.h>
//#include <cstdio>
//#include <cstring>
//#include <iostream>
//#include "game/constants.h"
//
//using namespace std;
//
//void server(int port) {
//    // abre un puerto cualquiera (via de mensajes)
//	UDPsocket sd = SDLNet_UDP_Open(port);
//    // si no consigue abrir
//	if (!sd) {
//        cout << "ERROR AL ABRIR EL SERVER" << endl;
//        //error(); 
//    }
//
//    // creacion de un packet (estructura de datos a enviar/recibir)
//	UDPpacket* p = SDLNet_AllocPacket(MAX_PACKET_SIZE); 
//    // si no consigue crear
//	if (!p) { 
//        cout << "ERROR AL CREAR EL PAQUETE" << endl;
//        //error(); 
//    }
//
//	char* buffer = reinterpret_cast<char*>(p->data);
//	SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(1);
//    cout << socketSet << endl;
//	SDLNet_UDP_AddSocket(socketSet, sd);
//    cout << sd << endl;
//
//    bool end = false;
//
//	while (!end) {
//		// TODO I: PROCESS DATA on socket sd
//		//actividad en clientes
//        if (SDLNet_CheckSockets(socketSet, SDL_MAX_UINT32) > 0) {
//            cout << "AAAA" << endl;
//        	if (SDLNet_SocketReady(sd)) {
//                cout << "BB" << endl;
//        		if (SDLNet_UDP_Recv(sd, p) > 0) {
//        			// print client’s message
//        			cout << "Client says: " << buffer << endl;
//        			// send a response
//        			memcpy(buffer, "Received!", 10);
//        			p->len = 10;
//        			SDLNet_UDP_Send(sd, -1, p);
//        		}
//        	}
//        }
//	}
//
//    //libera 
//	SDLNet_FreePacket(p); 
//	SDLNet_FreeSocketSet(socketSet);
//	SDLNet_UDP_Close(sd);
//}
//
//// conectar
//void client(char* host, int port) {
//    // coge el socket abierto 
//	UDPsocket sd = SDLNet_UDP_Open(0);
//	IPaddress srvadd; //direcion ip
//	if (SDLNet_ResolveHost(&srvadd, host, port) < 0) { 
//        //error(); 
//    }
//	UDPpacket* p = SDLNet_AllocPacket(MAX_PACKET_SIZE);
//	char* buffer = reinterpret_cast<char*>(p->data);
//	SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(1);
//	SDLNet_UDP_AddSocket(socketSet, sd);
//	while (1) {
//		// TODO I: PROCESS DATA on socket sd
//		cout << "Enter a message: ";
//		cin.getline(buffer, 255);
//		if (strcmp(buffer, "exit") == 0) { break; }
//		p->len = static_cast<int>(strlen(buffer)) + 1;
//		p->address = srvadd;
//		SDLNet_UDP_Send(sd, -1, p);
//		if (SDLNet_CheckSockets(socketSet, 3000) > 0) {
//			if (SDLNet_SocketReady(sd)) {
//				while (SDLNet_UDP_Recv(sd, p) > 0) {
//					cout << "Server says: " << buffer << endl;
//				}
//			}
//		}
//	}
//	SDLNet_FreePacket(p);
//	SDLNet_FreeSocketSet(socketSet);
//	SDLNet_UDP_Close(sd);
//}
//
//
//int main(int argc, char** argv) {
//    if (SDL_Init(0) == -1) {
//        printf("SDL_Init: %s\n", SDL_GetError());
//        exit(1);
//    }
//    if (SDLNet_Init() == -1) {
//        printf("SDLNet_Init: %s\n", SDLNet_GetError());
//        exit(2);
//    }
//
//    bool done = false;
//    if (argc == 2 && strcmp(argv[1], "server") == 0) {
//        printf("Starting server...\n");
//
//        server(PORT);
//    }
//    else if (argc == 2 && strcmp(argv[1], "client") == 0) {
//        printf("Starting client...\n");
//
//        // le pide la direccion IP a conectarse
//        printf("IP: ");
//        char host[1024];
//        fgets(host, 1024, stdin);
//        client(host, PORT);
//    }
//    else {
//        printf("Choose server or client\n");
//    }
//
//    SDLNet_Quit();
//    SDL_Quit();
//}


#include <SDL.h>
#include <SDL_net.h>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

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
        TCPsocket server, client;
        IPaddress ip;
        if (SDLNet_ResolveHost(&ip, NULL, 9999) == -1) {
            printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
            exit(1);
        }
        server = SDLNet_TCP_Open(&ip);
        if (!server) {
            printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
            exit(2);
        }
        while (!done) {
            /* try to accept a connection */
            client = SDLNet_TCP_Accept(server);
            if (!client) { /* no connection accepted */
                /*printf("SDLNet_TCP_Accept: %s\n",SDLNet_GetError()); */
                SDL_Delay(100); /*sleep 1/10th of a second */
                continue;
            }

            /* get the clients IP and port number */
            IPaddress* remoteip;
            remoteip = SDLNet_TCP_GetPeerAddress(client);
            if (!remoteip) {
                printf("SDLNet_TCP_GetPeerAddress: %s\n", SDLNet_GetError());
                continue;
            }

            /* print out the clients IP and port number */
            Uint32 ipaddr;
            ipaddr = SDL_SwapBE32(remoteip->host);
            printf("Accepted a connection from %d.%d.%d.%d port %hu\n", ipaddr >> 24,
                (ipaddr >> 16) & 0xff, (ipaddr >> 8) & 0xff, ipaddr & 0xff,
                remoteip->port);

            while (1) {
                /* read the buffer from client */
                char message[1024];
                int len = SDLNet_TCP_Recv(client, message, 1024);
                if (!len) {
                    printf("SDLNet_TCP_Recv: %s\n", SDLNet_GetError());
                    break;
                }
                /* print out the message */
                printf("Received: %.*s\n", len, message);
                if (message[0] == 'q') {
                    printf("Disconecting on a q\n");
                    break;
                }
                if (message[0] == 'Q') {
                    printf("Closing server on a Q.\n");
                    done = true;
                    break;
                }
            }
            SDLNet_TCP_Close(client);
        }
    }
    else if (argc == 2 && strcmp(argv[1], "client") == 0) {
        printf("Starting client...\n");
        IPaddress ip;
        TCPsocket tcpsock;

        if (SDLNet_ResolveHost(&ip, "192.168.1.2", 9999) == -1) {
            printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
            exit(1);
        }

        tcpsock = SDLNet_TCP_Open(&ip);
        if (!tcpsock) {
            printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
            exit(2);
        }

        while (1) {
            printf("message: ");
            char message[1024];
            fgets(message, 1024, stdin);
            int len = strlen(message);

            /* strip the newline */
            message[len - 1] = '\0';

            if (len) {
                int result;

                /* print out the message */
                printf("Sending: %.*s\n", len, message);

                result =
                    SDLNet_TCP_Send(tcpsock, message, len); /* add 1 for the NULL */
                if (result < len)
                    printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
            }

            if (len == 2 && tolower(message[0]) == 'q') {
                break;
            }
        }

        SDLNet_TCP_Close(tcpsock);
    }
    else {
        printf("Choose server or client\n");
    }

    SDLNet_Quit();
    SDL_Quit();
}


