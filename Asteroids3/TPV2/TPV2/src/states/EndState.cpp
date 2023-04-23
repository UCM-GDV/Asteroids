#include "EndState.h"

// Constructora
EndState::EndState(int result) : Manager() {
	// Mensajes
	resultEntity = new Entity(_grp_UI);
	resultEntity->setContext(this);
	addComponent<Transform>(resultEntity, GAME_OVER_TEXT_POSITION, VECTOR_ZERO, TEXT_WIDTH, TEXT_HEIGHT, 0);
	addEntity(resultEntity, _grp_UI);

	string resultString; unsigned long color;
	switch (result) {
	case 1: { resultString = GAME_OVER_WIN_TEXT; color = COLOR_GREEN; } break;
	case 2: { resultString = GAME_OVER_LOSE_TEXT; color = COLOR_RED; } break;
	case 3: { resultString = PLAYER1WINS; color = COLOR_GREEN; } break;
    case 4: { resultString = PLAYER2WINS; color = COLOR_GREEN; } break;
	default: { resultString = " "; color = COLOR_BLACK; } break;
	}
	UITextures_[resultEntity] = new Texture(SDLUtils::instance()->renderer(), resultString, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(color));

    continueEntity = new Entity(_grp_UI);
    continueEntity->setContext(this);
    addComponent<Transform>(continueEntity, TEXT_POSITION, VECTOR_ZERO, TEXT_WIDTH, TEXT_HEIGHT, 0);
    addEntity(continueEntity, _grp_UI);

	// Sistemas
	switch (result) {
    case 1: case 2: 
        UITextures_[continueEntity] = new Texture(sdlutils().renderer(), PRESS_TO_START_TEXT, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0x112233ff), build_sdlcolor(COLOR_WHITE));
		fighterSys_ = addSystem<FighterSystem>(2);
        gameCtrlSys_ = addSystem<GameCtrlSystem>(2);
        renderSys_ = addSystem<RenderSystem>(2);
		break;
	case 3: case 4: 
        UITextures_[continueEntity] = new Texture(sdlutils().renderer(), GO_TO_MAIN_MENU_TEXT, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0x112233ff), build_sdlcolor(COLOR_WHITE));
        gameCtrlSys_ = addSystem<GameCtrlSystem>(5);
        renderSys_ = addSystem<RenderSystem>(5);
		break;
	default: break;
	}
	
}