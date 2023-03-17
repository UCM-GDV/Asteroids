//#include "DisableOnExit.h"
//
//// Constructora
//DisableOnExit::DisableOnExit() : transform(nullptr) {}
//
//// Destructora
//DisableOnExit::~DisableOnExit() {
//	transform = nullptr;
//}
//// Inicializa el componente
//void DisableOnExit::initComponent() {
//	transform = ent_->getComponent<Transform>(_TRANSFORM);
//	assert(transform != nullptr);
//}
//// Actualiza el componente
//void DisableOnExit::update() {
//	if (transform->getPos().getX() < -(BULLET_WIDTH) || transform->getPos().getX()> (WIN_WIDTH + BULLET_WIDTH) || transform->getPos().getY() < -(BULLET_HEIGHT) || transform->getPos().getY()>( WIN_HEIGHT+ BULLET_HEIGHT)) {
//		ent_->setAlive(false);
//	}
//}