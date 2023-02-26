#include "fighter.h"

Fighter::Fighter(Game* _game) : Entity() {

	// TRANSFORM COMPONENT
	transform = addComponent<Transform>((int)(_TRANSFORM), Vector2D(WIN_WIDTH / 2, WIN_HEIGHT / 2), FIGHTER_VELOCITY, FIGHTER_WIDTH, FIGHTER_HEIGHT, FIGHTER_ROTATION);
	// IMAGE COMPONENT
	addComponent<Image>((int)(_IMAGE), &SDLUtils::instance()->images().at("Fighter"));
	addComponent<Health>((int)_HEALTH);
	fightercontrol = addComponent<FighterControl>((int)_FIGHTERCONTROL);
	addComponent<DeAcceleration>((int)(_DEACCELERATION));
	gun = addComponent<Gun>((int)_GUN);
}

void Fighter::handleEvent() {
	if (InputHandler::instance()->isKeyDown(SDLK_LEFT)) {
		//transform->changeRot(-2);
		fightercontrol->rotate(-50);

	}
	else if (InputHandler::instance()->isKeyDown(SDLK_RIGHT)) {
		//transform->changeRot(2);
		fightercontrol->rotate(50);
	}
	else if(InputHandler::instance()->isKeyDown(SDLK_UP)) {
		
		fightercontrol->acelerate();
		//transform->changeVel(100);
	}
	else if (InputHandler::instance()->isKeyDown(SDLK_s)) {
		gun->tryShoot();
	}
}
Fighter::~Fighter() {}