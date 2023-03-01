#include "Follow.h"
#include "../../ecs/Entity.h"
// Constructora
Follow::Follow(Transform* followObjectTransform_) {
	transform = ent_->getComponent<Transform>(_TRANSFORM);
	followObjectTransform = followObjectTransform_;
}

// Destructora
Follow::~Follow() {
	transform = nullptr;
}

// Inicializa el componente
void Follow::initComponent() {}

//
void Follow::update() {
	//Para los asteroides de tipo B, el componente Follow tiene que girar el vector de
	//	velocidad en un grado en cada iteración para que el asteroide vaya hacia el caza.Si v es
	//	el vector de velocidad del asteroide, p su posición, y q la posición del caza, se puede
	//	conseguir este efecto cambiando el vector de velocidad del asteroide a
	//	v.rotate(v.angle(q - p) > 0 ? 1.0f : -1.0f)
}