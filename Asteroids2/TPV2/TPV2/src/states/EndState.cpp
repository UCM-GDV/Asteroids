#include "EndState.h"

// Constructora
EndState::EndState(Game* game, string resultString) : Manager(), game(game) {
	// Anade fighter para que se muestre en pantalla 
	fighter = new Entity();
	fighter->setContext(this);
	fighter->addComponent<Transform>(_TRANSFORM, Vector2D(WIN_HALF_WIDTH, WIN_HALF_HEIGHT), FIGHTER_VELOCITY, FIGHTER_WIDTH, FIGHTER_HEIGHT, FIGHTER_ROTATION);
	fighter->addComponent<Image>(_IMAGE, &SDLUtils::instance()->images().at("Fighter"));
	addEntity(fighter, _grp_FIGHTER);

	result = new Entity();
	result->setContext(this);
	// Si has ganado
	if (resultString == "win") {
		result->addComponent<Transform>(_TRANSFORM, GAME_OVER_WIN_TEXT_POSITION, VECTOR_ZERO, GAME_OVER_WIN_TEXT_WIDTH, GAME_OVER_WIN_TEXT_HEIGHT, 0);
		result->addComponent<Image>(_IMAGE, game->getText(GAME_OVER_WIN_TEXT));
	}
	// Si has perdido
	else if (resultString == "lose") {
		result->addComponent<Transform>(_TRANSFORM, GAME_OVER_LOSE_TEXT_POSITION, VECTOR_ZERO, GAME_OVER_LOSE_TEXT_WIDTH, GAME_OVER_LOSE_TEXT_HEIGHT, 0);
		result->addComponent<Image>(_IMAGE, game->getText(GAME_OVER_LOSE_TEXT));
	}
	addEntity(result, _grp_MESSAGES);

	// Texto
	pressToStart = new Entity();
	pressToStart->setContext(this);
	pressToStart->addComponent<Transform>(_TRANSFORM, PRESS_TO_START_TEXT_POSITION, VECTOR_ZERO, PRESS_TO_START_TEXT_WIDTH, PRESS_TO_START_TEXT_HEIGHT, 0);
	pressToStart->addComponent<Image>(_IMAGE, game->getText(PRESS_TO_START_TEXT));
	addEntity(pressToStart, _grp_MESSAGES);
}

// Destructora
EndState::~EndState() {
	fighter = nullptr;
	result = nullptr;
	pressToStart = nullptr;
	game = nullptr;
}

// Recoge el input del usuario
void EndState::handleEvent() {
	/*SDL_Event event;
	if (SDL_PollEvent(&event)) {
		InputHandler::instance()->update(event);

		if (InputHandler::instance()->keyDownEvent()) {
            if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
				GameStateMachine::instance()->changeState(new PauseState(game));
            }
		}
	}*/
};

