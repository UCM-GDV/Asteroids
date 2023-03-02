#include "EndState.h"

// Constructora
EndState::EndState(string result) : Manager() {
	if (result == "win") {
		cout << "YOU WIN" << endl;
	}
	else if (result == "lose") {
		cout << "YOU LOSE" << endl;
	}
}

// 
void EndState::handleEvent() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		InputHandler::instance()->update(event);

		if (InputHandler::instance()->keyDownEvent()) {
            if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
				GameStateMachine::instance()->changeState(new PauseState());
            }
		}
	}
};

// Destructora
EndState::~EndState() {
}