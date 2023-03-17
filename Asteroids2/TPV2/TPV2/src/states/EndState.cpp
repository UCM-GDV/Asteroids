#include "EndState.h"

// Constructora
EndState::EndState(string resultString) : Manager() {
	// Anade fighter para que se muestre en pantalla 
	fighter = new Entity(_grp_FIGHTER);
	fighter->setContext(this);
	addComponent<Transform>(fighter, Vector2D(WIN_HALF_WIDTH, WIN_HALF_HEIGHT), FIGHTER_VELOCITY, FIGHTER_WIDTH, FIGHTER_HEIGHT, FIGHTER_ROTATION);
	addEntity(fighter, _grp_FIGHTER);

	result = new Entity(_grp_MESSAGES);
	result->setContext(this);
	// Si has ganado
	if (resultString == "win") {
		addComponent<Transform>(result, GAME_OVER_WIN_TEXT_POSITION, VECTOR_ZERO, GAME_OVER_WIN_TEXT_WIDTH, GAME_OVER_WIN_TEXT_HEIGHT, 0);
		//addComponent<Image>(_IMAGE, game->getText(GAME_OVER_WIN_TEXT));
	}
	// Si has perdido
	else if (resultString == "lose") {
		addComponent<Transform>(result, GAME_OVER_LOSE_TEXT_POSITION, VECTOR_ZERO, GAME_OVER_LOSE_TEXT_WIDTH, GAME_OVER_LOSE_TEXT_HEIGHT, 0);
		//result->addComponent<Image>(_IMAGE, game->getText(GAME_OVER_LOSE_TEXT));
	}
	addEntity(result, _grp_MESSAGES);

	// Texto
	pressToStart = new Entity(_grp_MESSAGES);
	pressToStart->setContext(this);
	addComponent<Transform>(pressToStart, PRESS_TO_START_TEXT_POSITION, VECTOR_ZERO, PRESS_TO_START_TEXT_WIDTH, PRESS_TO_START_TEXT_HEIGHT, 0);
	//pressToStart->addComponent<Image>(_IMAGE, game->getText(PRESS_TO_START_TEXT));
	addEntity(pressToStart, _grp_MESSAGES);

	addSystem<RenderSystem>();
}

// Destructora
EndState::~EndState() {
	fighter = nullptr;
	result = nullptr;
	pressToStart = nullptr;
}

// Recoge el input del usuario
//void EndState::handleEvent() {
//	/*SDL_Event event;
//	if (SDL_PollEvent(&event)) {
//		InputHandler::instance()->update(event);

//		if (InputHandler::instance()->keyDownEvent()) {
//            if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
//				GameStateMachine::instance()->changeState(new PauseState(game));
//            }
//		}
//	}*/
//};

