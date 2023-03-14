#include "Follow.h"
#include "../../ecs/Manager.h"
// Constructora
Follow::Follow(Transform* followObjectTransform_): transform(nullptr) {
	followObjectTransform = followObjectTransform_;
	assert(followObjectTransform != nullptr);
}

// Destructora
Follow::~Follow() {
	transform = nullptr;
	followObjectTransform = nullptr;
}

// Inicializa el componente
void Follow::initComponent() {
	transform = mngr_->getComponent<Transform>(ent_);
}

// Actualiza su vector de velocidad para perseguir al fighter
void Follow::update() {
	Vector2D v = transform->getVel();
	Vector2D p = transform->getPos();
	Vector2D q = followObjectTransform->getPos();
	transform->setVel(transform->getVel().rotate(v.angle(q - p) > 0 ? 1.0f : -1.0f));
}