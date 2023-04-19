#include "EndState.h"

// Constructora
EndState::EndState(int result) : Manager() {
	// Mensajes
	resultEntity = new Entity(_grp_MESSAGES);
	resultEntity->setContext(this);
	addComponent<Transform>(resultEntity, GAME_OVER_TEXT_POSITION, VECTOR_ZERO, TEXT_WIDTH, TEXT_HEIGHT, 0);
	addEntity(resultEntity, _grp_MESSAGES);

	string resultString; unsigned long color;
	switch (result) {
	case 1: { resultString = GAME_OVER_WIN_TEXT; color = COLOR_GREEN; } break;
	case 2: { resultString = GAME_OVER_LOSE_TEXT; color = COLOR_RED; } break;
	default: { resultString = " "; color = COLOR_BLACK; } break;
	}
	textTextures_[resultEntity] = new Texture(SDLUtils::instance()->renderer(), resultString, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(color));

	pressToStartEntity = new Entity(_grp_MESSAGES);
	pressToStartEntity->setContext(this);
	addComponent<Transform>(pressToStartEntity, TEXT_POSITION, VECTOR_ZERO, TEXT_WIDTH, TEXT_HEIGHT, 0);
	addEntity(pressToStartEntity, _grp_MESSAGES);
	textTextures_[pressToStartEntity] = new Texture(sdlutils().renderer(), PRESS_TO_START_TEXT, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0x112233ff), build_sdlcolor(0xffffffff));

	// Sistemas
	fighterSys_ = addSystem<FighterSystem>(2);
	gameCtrlSys_ = addSystem<GameCtrlSystem>(2);
	renderSys_ = addSystem<RenderSystem>(2);
}