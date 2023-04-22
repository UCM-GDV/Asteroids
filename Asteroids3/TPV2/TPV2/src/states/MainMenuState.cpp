#include "MainMenuState.h"
#include "../game/GameStateMachine.h"
#include "../states/PlayState.h"
#include "../states/PauseState.h"
#include "../states/PlayStateMultiplayer.h"

// Constructora
MainMenuState::MainMenuState() {
	// SISTEMAS
	fighterSys_ = addSystem<FighterSystem>(-1);
	gameCtrlSys_ = addSystem<GameCtrlSystem>(-1);
	renderSys_ = addSystem<RenderSystem>(-1);

	// BOTONES INICIALES
	onePlayerButton = new Entity(_grp_UI);
	onePlayerButton->setContext(this);
	addComponent<Transform>(onePlayerButton, ONEPLAYER_BUTTON_POSITION, VECTOR_ZERO, BUTTON_WIDTH, BUTTON_HEIGHT, 0);
	UITextures_[onePlayerButton] = new Texture(SDLUtils::instance()->renderer(), ONEPLAYER_TEXT, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(COLOR_BLACK), build_sdlcolor(COLOR_WHITE));
	addComponent<Callback>(onePlayerButton, [&]() { goToPlayState(); });
	addEntity(onePlayerButton, _grp_UI);
	
	multiPlayerButton = new Entity(_grp_UI);
	multiPlayerButton->setContext(this);
	addComponent<Transform>(multiPlayerButton, MULTIPLAYER_BUTTON_POSITION, VECTOR_ZERO, BUTTON_WIDTH, BUTTON_HEIGHT, 0);
	UITextures_[multiPlayerButton] = new Texture(SDLUtils::instance()->renderer(), MULTIPLAYER_TEXT, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(COLOR_BLACK), build_sdlcolor(COLOR_WHITE));
	addComponent<Callback>(multiPlayerButton, [&]() { goToPlayStateMultiplayer(); });
	addEntity(multiPlayerButton, _grp_UI);

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
}

// Destructora
MainMenuState::~MainMenuState() {}

void MainMenuState::goToPlayState() {
	GameStateMachine::instance()->popState();
	GameStateMachine::instance()->pushState(new PlayState());
	GameStateMachine::instance()->pushState(new PauseState());
}

void MainMenuState::goToPlayStateMultiplayer() {
	GameStateMachine::instance()->popState();
	GameStateMachine::instance()->pushState(new PlayStateMultiPlayer());
}