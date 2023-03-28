#include "EndState.h"

// Constructora
EndState::EndState(string resultString) : Manager() {
	if (resultString == "win") {
		textTexture_ = new Texture(SDLUtils::instance()->renderer(), GAME_OVER_WIN_TEXT, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0x00ff00ff));
	}
	else {
		textTexture_ = new Texture(SDLUtils::instance()->renderer(), GAME_OVER_LOSE_TEXT, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0xff0000ff));
	}
	
	

	//// Texto
	//pressToStart = new Entity(_grp_MESSAGES);
	//pressToStart->setContext(this);
	//addComponent<Transform>(pressToStart, PRESS_TO_START_TEXT_POSITION, VECTOR_ZERO, PRESS_TO_START_TEXT_WIDTH, PRESS_TO_START_TEXT_HEIGHT, 0);
	////pressToStart->addComponent<Image>(_IMAGE, game->getText(PRESS_TO_START_TEXT));
	//addEntity(pressToStart, _grp_MESSAGES);

	//addSystem<RenderSystem>();
}

// Destructora
EndState::~EndState() {
}