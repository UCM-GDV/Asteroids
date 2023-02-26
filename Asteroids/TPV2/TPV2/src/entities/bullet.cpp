//position_ = position_
//+ Vector2D(width_ / 2.0f, height_ / 2.0f)
//- Vector2D(0.0f, height_ / 2.0f + 5.0f + 12.0f).rotate(rotation_)
//- Vector2D(2.0f, 10.0f);
//velocity_ = Vector2D(0.0f, -1.0f).rotate(rotation_) * (velocity_.magnitude() + 5.0f);
//
//cout << velocity_.getX() << " " << velocity_.getY() << endl;
//cout << position_.getX() << " " << position_.getY() << endl;

#include "bullet.h"

// Constructora
Bullet::Bullet(Fighter* fighter) {

	Transform* fighterTransform = fighter->getComponent<Transform>();

	transform = addComponent<Transform>((int)_TRANSFORM, fighterTransform->getPos(), fighterTransform->getVel, BULLET_WIDTH, BULLET_HEIGHT, fighterTransform->getRot());
	addComponent<Image>((int)_IMAGE, &SDLUtils::instance()->images().at("Bullet"));
	addComponent<DisableOnExit>((int)_DISABLEONEXIT);
}

// Destructora
Bullet::~Bullet() {
	transform = nullptr;
}