#include "PauseState.h"

// Constructora
PauseState::PauseState() : Manager() {
	fighter = new Entity();
	fighter->setContext(this);
	fighter->addComponent<Transform>(_TRANSFORM, Vector2D(WIN_HALF_WIDTH, WIN_HALF_HEIGHT), FIGHTER_VELOCITY, FIGHTER_WIDTH, FIGHTER_HEIGHT, FIGHTER_ROTATION);
	fighter->addComponent<Image>(_IMAGE, &SDLUtils::instance()->images().at("Fighter"));
	fighter->addComponent<Health>(_HEALTH);
	addEntity(fighter);
}
void PauseState::handleEvent() {
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		InputHandler::instance()->update(event);

        if (InputHandler::instance()->keyDownEvent()) {
            if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
				GameStateMachine::instance()->popState();
            }
        }
	}
};
// Destructora
PauseState::~PauseState() {
}