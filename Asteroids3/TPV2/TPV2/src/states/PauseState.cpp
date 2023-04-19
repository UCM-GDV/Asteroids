#include "PauseState.h"

// Constructora
PauseState::PauseState() : Manager() {
	// Sistemas
	fighterSys_ = addSystem<FighterSystem>(0);
	gameCtrlSys_ = addSystem<GameCtrlSystem>(0);
	renderSys_ = addSystem<RenderSystem>(0);

	pressToContinue = new Entity(_grp_MESSAGES);
	pressToContinue->setContext(this);
	addComponent<Transform>(pressToContinue, TEXT_POSITION, VECTOR_ZERO, TEXT_WIDTH, TEXT_HEIGHT, 0);
	addEntity(pressToContinue, _grp_MESSAGES);
	textTextures_[pressToContinue] = new Texture(sdlutils().renderer(), PRESS_TO_CONTINUE_TEXT, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0x112233ff), build_sdlcolor(COLOR_WHITE));
}

// Destructora
PauseState::~PauseState() {}

