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
	Vector2D bPos, bVel;
	bPos = fighterTransform->getPos()
		+ Vector2D(FIGHTER_WIDTH / 2.0f, FIGHTER_HEIGHT / 2.0f)
		- Vector2D(0.0f, FIGHTER_HEIGHT / 2.0f + 5.0f + 12.0f).rotate(fighterTransform->getR())
		- Vector2D(2.0f, 10.0f);
	bVel = Vector2D(0.0f, -1.0f).rotate(fighterTransform->getR()) * (fighterTransform->getVel().magnitude() + 5.0f);

	bullet->addComponent<Transform>(_TRANSFORM, bPos, bVel, BULLET_WIDTH, BULLET_HEIGHT, fighterTransform->getR());
	bullet->addComponent<Image>(_IMAGE, &SDLUtils::instance()->images().at("Bullet"));
	bullet->addComponent<DisableOnExit>(_DISABLEONEXIT);
	bullet->addToGroup(_grp_BULLETS);
	addEntity(bullet);
}