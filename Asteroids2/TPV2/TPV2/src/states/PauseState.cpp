#include "PauseState.h"

// Constructora
PauseState::PauseState() : Manager() {

	fighterSys_ = addSystem<FighterSystem>(0);
	gameCtrlSys_ = addSystem<GameCtrlSystem>(0);
	renderSys_ = addSystem<RenderSystem>(0);

	//// Anade texto
	//pressToContinue = new Entity(_grp_MESSAGES);
	//pressToContinue->setContext(this);
	//addComponent<Transform>(pressToContinue, PRESS_TO_CONTINUE_TEXT_POSITION, VECTOR_ZERO, PRESS_TO_CONTINUE_TEXT_WIDTH, PRESS_TO_CONTINUE_TEXT_HEIGHT, 0);
	////pressToContinue->addComponent<Image>(_IMAGE, game->getText(PRESS_TO_CONTINUE_TEXT));
	//addEntity(pressToContinue, _grp_MESSAGES);

	// Sistema de renderizado
	//renderSystem = addSystem<RenderSystem>();
}

// Destructora
PauseState::~PauseState() {
	/*fighter = nullptr;
	pressToContinue = nullptr;*/
}

