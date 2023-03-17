#include "PauseState.h"

// Constructora
PauseState::PauseState() : Manager() {
	// Anade fighter para que se muestre en pantalla 
	fighter = new Entity(_grp_FIGHTER);
	fighter->setContext(this);
	addComponent<Transform>(fighter, Vector2D(WIN_HALF_WIDTH, WIN_HALF_HEIGHT), FIGHTER_VELOCITY, FIGHTER_WIDTH, FIGHTER_HEIGHT, FIGHTER_ROTATION);
	//fighter->addComponent<Image>(_IMAGE, &SDLUtils::instance()->images().at("Fighter"));
	addComponent<Health>(fighter);
	addEntity(fighter, _grp_FIGHTER);

	// Anade texto
	pressToContinue = new Entity(_grp_MESSAGES);
	pressToContinue->setContext(this);
	addComponent<Transform>(pressToContinue, PRESS_TO_CONTINUE_TEXT_POSITION, VECTOR_ZERO, PRESS_TO_CONTINUE_TEXT_WIDTH, PRESS_TO_CONTINUE_TEXT_HEIGHT, 0);
	//pressToContinue->addComponent<Image>(_IMAGE, game->getText(PRESS_TO_CONTINUE_TEXT));
	addEntity(pressToContinue, _grp_MESSAGES);

	// Sistema de renderizado
	renderSystem = addSystem<RenderSystem>();
}

// Destructora
PauseState::~PauseState() {
	fighter = nullptr;
	pressToContinue = nullptr;
}

// Recoge el input del usuario
void PauseState::handleEvent() {
	/*SDL_Event event;
	if (SDL_PollEvent(&event)) {
		InputHandler::instance()->update(event);

        if (InputHandler::instance()->keyDownEvent()) {
            if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
				GameStateMachine::instance()->popState();
            }
			else if (InputHandler::instance()->isKeyDown(SDLK_ESCAPE)) {
				game->exitGame();
			}
        }
	}*/
};
