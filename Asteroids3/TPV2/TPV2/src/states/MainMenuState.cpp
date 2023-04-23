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
}

// DESTRUCTORA
MainMenuState::~MainMenuState() {
	onePlayerButton = nullptr;
	multiPlayerButton = nullptr;
}

//CAMBIA DEL MAIN-MENU AL PAUSE 
void MainMenuState::goToPlayState() {
	GameStateMachine::instance()->popState();
	GameStateMachine::instance()->pushState(new PlayState());
	GameStateMachine::instance()->pushState(new PauseState());
}
//CAMBIA DEL MAIN-MENU AL MULTI-PLAYER
void MainMenuState::goToPlayStateMultiplayer() {
	GameStateMachine::instance()->popState();
	GameStateMachine::instance()->pushState(new PlayStateMultiPlayer());
}