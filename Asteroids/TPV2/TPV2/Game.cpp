#include <SDL.h>
#include "src/sdlutils/Game.h"
#include "src/sdlutils/InputHandler.h"
#include "src/sdlutils/macros.h"
#include "src/sdlutils/SDLUtils.h"

using namespace std;

void Game() {

	// Initialise the SDLGame singleton
	SDLUtils::init("Asteroids", 600, 600,
		"resources/config/sdlutilsdemo.resources.json");

	// reference to the SDLUtils Singleton. You could use it as a pointer as well,
	// I just prefer to use . instead of ->, it is just a matter of taste, nothing
	// else!
	//
	// you can also use the inline method sdlutils() that simply returns the value
	// of *SDLUtils::instance() --- it is defined at the end of SDLUtils.h
	//
	auto& sdl = *SDLUtils::instance();

	//show the cursor
	sdl.showCursor();

	// store the 'renderer' in a local variable, just for convenience
	SDL_Renderer* renderer = sdl.renderer();

	// reference to the input handler (we could use a pointer, I just . rather than ->).
	// you can also use the inline method ih() that is defined in InputHandler.h
	auto& ih = *InputHandler::instance();

	// a boolean to exit the loop
	bool exit_ = false;

	while (!exit_) {
		Uint32 startTime = sdl.currRealTime();

		// update the event handler
		ih.refresh();

		// exit when any key is down
		if (ih.keyDownEvent())
			exit_ = true;

		// clear screen
		sdl.clearRenderer();

		// present new frame
		sdl.presentRenderer();

		Uint32 frameTime = sdl.currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

	// stop the music
	Music::haltMusic();

}

