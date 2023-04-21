#include "MainMenuState.h"
#include "../game/GameStateMachine.h"
#include "../states/PlayState.h"
#include "../states/PauseState.h"
#include "../states/PlayStateMultiplayer.h"

// Constructora
MainMenuState::MainMenuState() : hostButton(nullptr), clientButton(nullptr), enterButton(nullptr), nameTextBox(nullptr), waitingText(nullptr), ipTextBox(nullptr) {
	fighterSys_ = addSystem<FighterSystem>(-1);
	gameCtrlSys_ = addSystem<GameCtrlSystem>(-1);
	renderSys_ = addSystem<RenderSystem>(-1);

	// enviar posicion y rotacion si se recarga con poco tiempo tambien la velocidad
	// hacerlo a traves de los socketssets
	// se puede crear un componente que lea los mensajes que reciba (una nave tiene fighter control y laotra networkfightercobtrol)
	// añadir mensajes con informacion tipo morir y coliosion victoria...
	//cada uno controla la suya y se avisan mutuamente o el server sea el que se encarge de comprobar todas las colisiones (ESTA ES LA MEJOR)
	// se puede hacer a traves de componentes uno mediente red(comentario 3 ) o utilizando sistemas (lo que nos recomienda)
	// sistema de red nos encargamos de enviar y recibir los mensajes y estos enviaran un mensaje que lo reciviran el resto 
	// si el servidor cae se produce en el nuevo sistema (poner try catch)
	// opcion de volver a establecer conexion si se pierde la comunicacion
	// asteroides no hay en multijugador

	// En el RenderSystem, dibujar los botones
	// En el GameCtrlSystem, gestionar el click del boton


	// BOTONES INICIALES
	onePlayerButton = new Entity(_grp_BUTTONS);
	onePlayerButton->setContext(this);
	addComponent<Transform>(onePlayerButton, ONEPLAYER_BUTTON_POSITION, VECTOR_ZERO, BUTTON_WIDTH, BUTTON_HEIGHT, 0);
	textTextures_[onePlayerButton] = new Texture(SDLUtils::instance()->renderer(), ONEPLAYER_TEXT, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(COLOR_BLACK), build_sdlcolor(COLOR_WHITE));
	addComponent<Callback>(onePlayerButton, []() {
		GameStateMachine::instance()->popState();
		GameStateMachine::instance()->pushState(new PlayState());
		GameStateMachine::instance()->pushState(new PauseState()); });
	addEntity(onePlayerButton, _grp_BUTTONS);
	
	multiPlayerButton = new Entity(_grp_BUTTONS);
	multiPlayerButton->setContext(this);
	addComponent<Transform>(multiPlayerButton, MULTIPLAYER_BUTTON_POSITION, VECTOR_ZERO, BUTTON_WIDTH, BUTTON_HEIGHT, 0);
	textTextures_[multiPlayerButton] = new Texture(SDLUtils::instance()->renderer(), MULTIPLAYER_TEXT, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(COLOR_BLACK), build_sdlcolor(COLOR_WHITE));
	addComponent<Callback>(multiPlayerButton, [&]() {
		// CREAR LOS BOTONES DE HOST Y CLIENT
		createHostButton();
		createClientButton();

		// QUITAR LOS BOTONES DE ONEPLAYER Y MULTIPLAYER
		onePlayerButton->setAlive(false);
		multiPlayerButton->setAlive(false);
	});
	addEntity(multiPlayerButton, _grp_BUTTONS);

	if (SDLNet_Init() < 0) {
		throw SDLNet_GetError();
	}
}

// Destructora
MainMenuState::~MainMenuState() {
	SDLNet_Quit();
}

// Crea servidor
void MainMenuState::server(const int port) {
	// abre un puerto cualquiera (via de mensajes)
	UDPsocket sd = SDLNet_UDP_Open(port);
	// si no consigue abrir
	if (!sd) {
		throw("ERROR AL ABRIR EL SERVER");
	}

	// creacion de un packet (estructura de datos a enviar/recibir)
	UDPpacket* p = SDLNet_AllocPacket(MAX_PACKET_SIZE);
	// si no consigue crear
	if (!p) {
		throw("ERROR AL CREAR EL PAQUETE");
	}

	char* buffer = reinterpret_cast<char*>(p->data);
	SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(1);
	SDLNet_UDP_AddSocket(socketSet, sd);

	// MODIFICAR ESTE CODIGO PARA QUE SEA NUESTRO JUEGO
	
	bool end = false;
	cout << "ENTRA" << endl;
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
void MainMenuState::client(const char* host, const int port) {
    // coge el socket abierto 
	UDPsocket sd = SDLNet_UDP_Open(0);
	IPaddress srvadd; //direcion ip
	if (SDLNet_ResolveHost(&srvadd, host, port) < 0) { 
		throw("ERROR AL ESTABLECER CONEXION CON EL SERVIDOR");
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

// UI
void MainMenuState::createHostButton() {
	hostButton = new Entity(_grp_BUTTONS);
	hostButton->setContext(this);
	addComponent<Transform>(hostButton, ONEPLAYER_BUTTON_POSITION, VECTOR_ZERO, BUTTON_WIDTH, BUTTON_HEIGHT, 0);
	textTextures_[hostButton] = new Texture(SDLUtils::instance()->renderer(), HOST_TEXT, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(COLOR_BLACK), build_sdlcolor(COLOR_WHITE));
	addComponent<Callback>(hostButton, [&]() {
		createNameTextBox();
		createEnterButton(false);

		// QUITAR LOS BOTONES DE HOST Y CLIENT
		hostButton->setAlive(false);
		clientButton->setAlive(false);
	});
	addEntity(hostButton, _grp_BUTTONS);
}

void MainMenuState::createClientButton() {
	clientButton = new Entity(_grp_BUTTONS);
	clientButton->setContext(this);
	addComponent<Transform>(clientButton, MULTIPLAYER_BUTTON_POSITION, VECTOR_ZERO, BUTTON_WIDTH, BUTTON_HEIGHT, 0);
	textTextures_[clientButton] = new Texture(SDLUtils::instance()->renderer(), CLIENT_TEXT, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(COLOR_BLACK), build_sdlcolor(COLOR_WHITE));
	addComponent<Callback>(clientButton, [&]() {
		createNameTextBox();
		createEnterButton(true);

		// QUITAR LOS BOTONES DE HOST Y CLIENT
		hostButton->setAlive(false);
		clientButton->setAlive(false);

		// ASIGNA DE QUE SE TRATA DEL CLIENTE
		
	});
	addEntity(clientButton, _grp_BUTTONS);
}

void MainMenuState::createEnterButton(bool player) {
	enterButton = new Entity(_grp_BUTTONS);
	enterButton->setContext(this);
	addComponent<Transform>(enterButton, MULTIPLAYER_BUTTON_POSITION, VECTOR_ZERO, BUTTON_WIDTH, BUTTON_HEIGHT, 0);
	textTextures_[enterButton] = new Texture(SDLUtils::instance()->renderer(), ENTER_TEXT, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(COLOR_WHITE), build_sdlcolor(COLOR_RED));

	// Si se trata del jugador 1
	if (!player) {
		addComponent<Callback>(enterButton, [&]() {
			// Anade texto de espera
			waitingText = new Entity(_grp_MESSAGES);
			waitingText->setContext(this);
			addComponent<Transform>(waitingText, ONEPLAYER_BUTTON_POSITION, VECTOR_ZERO, BUTTON_WIDTH, BUTTON_HEIGHT, 0);
			textTextures_[waitingText] = new Texture(SDLUtils::instance()->renderer(), WAITING_TEXT, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(COLOR_BLACK), build_sdlcolor(COLOR_WHITE));
			addEntity(waitingText, _grp_MESSAGES);

			// Quita el textbox del nombre
			nameTextBox->setAlive(false);
			// Quita el boton de enter
			enterButton->setAlive(false);
			
			// ASIGNA DE QUE SE TRATA DEL HOST
			server(PORT);
		});
	}
	// Si se trata del jugador 2
	else {
		addComponent<Callback>(enterButton, [&]() {
			// Anade textbox de IP
			ipTextBox = new Entity(_grp_TEXTBOXS);
			ipTextBox->setContext(this);
			addComponent<Transform>(ipTextBox, ONEPLAYER_BUTTON_POSITION, VECTOR_ZERO, BUTTON_WIDTH, BUTTON_HEIGHT, 0);
			textTextures_[ipTextBox] = new Texture(SDLUtils::instance()->renderer(), IP_TEXT, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(COLOR_BLACK), build_sdlcolor(COLOR_WHITE));
			addEntity(ipTextBox, _grp_TEXTBOXS);

			// Reescribe el callback del boton de enter
			
			getComponent<Callback>(enterButton)->setCallback([&]() {
				// TODO COMPROBAR QUE LA IP ES VALIDA
				client(getComponent<Callback>(enterButton)->ip, PORT);
				
				ipTextBox->setAlive(false);
				enterButton->setAlive(false);
			});

			// Quita el textbox del nombre
			nameTextBox->setAlive(false);
		});
	}

	addEntity(enterButton, _grp_BUTTONS);
}

void MainMenuState::createNameTextBox() {
	nameTextBox = new Entity(_grp_TEXTBOXS);
	nameTextBox->setContext(this);
	addComponent<Transform>(nameTextBox, ONEPLAYER_BUTTON_POSITION, VECTOR_ZERO, BUTTON_WIDTH, BUTTON_HEIGHT, 0);
	textTextures_[nameTextBox] = new Texture(SDLUtils::instance()->renderer(), NAME_TEXT_BOX, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(COLOR_BLACK), build_sdlcolor(COLOR_WHITE));
	addEntity(nameTextBox, _grp_TEXTBOXS);
}