#include "PauseState.h"
// Constructora
PauseState::PauseState() : Manager() {
	fighter = new Entity();
	fighter->setContext(this);
	fighter->addComponent<Transform>(_TRANSFORM, Vector2D(WIN_HALF_WIDTH, WIN_HALF_HEIGHT), FIGHTER_VELOCITY, FIGHTER_WIDTH, FIGHTER_HEIGHT, FIGHTER_ROTATION);
	fighter->addComponent<Image>(_IMAGE, &SDLUtils::instance()->images().at("Fighter"));
	fighter->addComponent<Health>(_HEALTH);
	addEntity(fighter);

	//Texture(SDL_Renderer * renderer, const std::string & text, const Font & font,
	//	const SDL_Color & fgColor)
	//auto& sdl = *SDLUtils::instance();
	//SDL_Renderer* renderer = sdl.renderer();
	//const Font* a = &SDLUtils::instance()->fonts().at("ARIAL24");
	//const string text = "Press space to continue";

	//Texture(SDL_Renderer * renderer, const std::string & text, const Font & font,
		//const SDL_Color & fgColor);
	//Texture pressAnyKey(renderer, text,
	//	a, build_sdlcolor(0x112233ff),
	//	build_sdlcolor(0xffffffff));
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

void PauseState::render() const {
	//pressSpaceToContinue.render(0,0);
}

// Destructora
PauseState::~PauseState() {
}