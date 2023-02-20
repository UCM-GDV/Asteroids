#include "fighter.h"

Fighter::Fighter(Game* _game) : Entity() {

	// TRANSFORM COMPONENT
	transform = addComponent<Transform>((int)(_TRANSFORM), Vector2D(WIN_WIDTH / 2, WIN_HEIGHT / 2), FIGHTER_VELOCITY, FIGHTER_WIDTH, FIGHTER_HEIGHT, FIGHTER_ROTATION);
	// IMAGE COMPONENT
	addComponent<Image>((int)(_IMAGE), &SDLUtils::instance()->images().at("Fighter"));
	addComponent<DeAcceleration>((int)(_DEACCELERATION));
	addComponent<Health>((int)_HEALTH);
}
//
//void Fighter::update() {
//	if (transform->getVel().getY() >= 0) {
//		Vector2D vel = transform->getVel() +Vector2D(0.0f, -1.0f).rotate(transform->getR()) * 0.2f;
//		transform->setVel(vel);
//		/*Vector2D pos = transform->getPos()
//			+ Vector2D(transform->getW() / 2.0f, transform->getH() / 2.0f)
//			- Vector2D(0.0f, transform->getH() / 2.0f + 5.0f + 12.0f).rotate(transform->getR())
//			- Vector2D(2.0f, 10.0f);*/
//		Vector2D pos = transform->getPos() + vel;
//		transform->setPos(pos);
//		cout << transform->getVel() << endl;
//		//transform->setPos(pos);
//	}
//
//	
//	
//}

void Fighter::handleEvent() {
	/*if (InputHandler::instance()->isKeyDown(SDLK_LEFT)) {
		transform->changeRot(-2);
	}
	else if (InputHandler::instance()->isKeyDown(SDLK_RIGHT)) {
		transform->changeRot(2);
	}*/
	if (InputHandler::instance()->isKeyDown(SDLK_UP)) {
		transform->changeVel(100);
	}
}
Fighter::~Fighter() {}