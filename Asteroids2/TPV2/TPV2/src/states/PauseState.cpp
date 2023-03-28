#include "PauseState.h"

// Constructora
PauseState::PauseState() : Manager() {
	// Sistemas
	fighterSys_ = addSystem<FighterSystem>(0);
	gameCtrlSys_ = addSystem<GameCtrlSystem>(0);
	renderSys_ = addSystem<RenderSystem>(0);

	// Crea la textura
	textTexture_ = new Texture(sdlutils().renderer(), PRESS_TO_CONTINUE_TEXT, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0x112233ff), build_sdlcolor(0xffffffff));
}

// Destructora
PauseState::~PauseState() {}

