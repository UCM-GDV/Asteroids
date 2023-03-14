#include "DeAcceleration.h"
#include "../../ecs/Manager.h"
// Constructora 
DeAcceleration::DeAcceleration() : transform(nullptr) {}
// Destructora 
 DeAcceleration::~DeAcceleration() {};
 // Inicializa el componente
void DeAcceleration::initComponent() {
	transform = mngr_->getComponent<Transform>(ent_);
	assert(transform != nullptr);
}
// Actualiza el componente
void DeAcceleration::update() {
	Vector2D vel = transform->getVel();
	if (abs(vel.getY()) < 0.05f) transform->setVel(Vector2D(0,0));
	else transform->setVel(vel * 0.995f);
}