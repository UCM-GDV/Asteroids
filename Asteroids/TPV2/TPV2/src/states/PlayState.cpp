#include "PlayState.h"

// Constructora
PlayState::PlayState(): Manager()  {

	// FIGHTER
	fighter = new Entity();
	fighter->setContext(this);
	fighterTransform = fighter->addComponent<Transform>(_TRANSFORM, Vector2D(WIN_WIDTH / 2, WIN_HEIGHT / 2), FIGHTER_VELOCITY, FIGHTER_WIDTH, FIGHTER_HEIGHT, FIGHTER_ROTATION);
	fighter->addComponent<Image>(_IMAGE, &SDLUtils::instance()->images().at("Fighter"));
	fighter->addComponent<Health>(_HEALTH);
	fighterControl = fighter->addComponent<FighterControl>(_FIGHTERCONTROL);
	fighter->addComponent<DeAcceleration>(_DEACCELERATION);
	fighterGun = fighter->addComponent<Gun>(_GUN);
	fighter->addComponent<ShowAtOppositeSide>(_SHOWATOPPOSIDESIDE);
	addEntity(fighter);
	// ASTEROIDES
	asteroid = new Entity();
	asteroid->setContext(this);
	// TRANSFORM COMPONENT
	asteroid->addComponent<Transform>((int)(_TRANSFORM), Vector2D(WIN_WIDTH / 2, WIN_HEIGHT / 2), Vector2D(0, 0), ASTEROID_WIDTH_1, ASTEROID_HEIGHT_1, 0);
	// IMAGE COMPONENT
	asteroid->addComponent<FramedImage>((int)(_FRAMEDIMAGE), &SDLUtils::instance()->images().at("WhiteAsteroid"), ASTEROID_WHITE_WIDTH, ASTEROID_WHITE_HEIGHT, ASTEROID_WHITE_NUMCOLS, ASTEROID_WHITE_NUMROWS);
	addEntity(asteroid);
	asteroid->addToGroup(_grp_ASTEROIDS);

}

// Destructora
PlayState::~PlayState() {
	fighter = nullptr;
	fighterTransform = nullptr;
	fighterGun = nullptr;
	fighterControl = nullptr;
}

void PlayState::addBullet() {
	Entity* bullet = new Entity();
	bullet->addComponent<Transform>(_TRANSFORM, Vector2D(fighterTransform->getPos().getX() + FIGHTER_WIDTH / 2, fighterTransform->getPos().getY() + 50), fighterTransform->getVel(), BULLET_WIDTH, BULLET_HEIGHT, fighterTransform->getR());
	bullet->addComponent<Image>(_IMAGE, &SDLUtils::instance()->images().at("Bullet"));
	addEntity(bullet);
}