#include "EndState.h"

// Constructora
EndState::EndState(string result) : Manager() {
	// MENSAJE DE QUIEN HA GANADO
	resultEntity = new Entity(_grp_UI);
	resultEntity->setContext(this);
	addComponent<Transform>(resultEntity, GAME_OVER_TEXT_POSITION, VECTOR_ZERO, TEXT_WIDTH, TEXT_HEIGHT, 0);
	addEntity(resultEntity, _grp_UI);
	//MENSAJE PARA IDICAR QUE PUEDE CONTINUAR
    continueEntity = new Entity(_grp_UI);
    continueEntity->setContext(this);
    addComponent<Transform>(continueEntity, TEXT_POSITION, VECTOR_ZERO, TEXT_WIDTH, TEXT_HEIGHT, 0);
    addEntity(continueEntity, _grp_UI);

	string resultString, continueString; unsigned long color;
	if (result == GAME_OVER_WIN_TEXT) {//SI HAS GANADO
		resultString = result;
		color = COLOR_GREEN;
		continueString = PRESS_TO_START_TEXT;

		fighterSys_ = addSystem<FighterSystem>(2);
		gameCtrlSys_ = addSystem<GameCtrlSystem>(2);
		renderSys_ = addSystem<RenderSystem>(2);
	}
	else if (result == GAME_OVER_LOSE_TEXT) {//SI HAS PERDIDO
		resultString = result;
		color = COLOR_RED;
		continueString = PRESS_TO_START_TEXT;

		fighterSys_ = addSystem<FighterSystem>(2);
		gameCtrlSys_ = addSystem<GameCtrlSystem>(2);
		renderSys_ = addSystem<RenderSystem>(2);
	}
	else {//INDICA CUAL DE LOS DOS HA GANADO
		resultString = result + " wins!";
		color = COLOR_GREEN;
		continueString = GO_TO_MAIN_MENU_TEXT;

        gameCtrlSys_ = addSystem<GameCtrlSystem>(5);
        renderSys_ = addSystem<RenderSystem>(5);
	}

	UITextures_[resultEntity] = new Texture(SDLUtils::instance()->renderer(), resultString, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(color));
    UITextures_[continueEntity] = new Texture(sdlutils().renderer(), continueString, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(COLOR_BLACK), build_sdlcolor(COLOR_WHITE));
}