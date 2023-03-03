#pragma once
#include "../sdlutils/Texture.h"
#include "Transform.h"

class Image: public Component {
private:
	// Consulta las caracteristicas fisicas
	Transform* tr_;
	// Imagen a rederizar
	Texture* tex_;
public:
	// Constructora
	Image(Texture* tex) : tr_(nullptr), tex_(tex) {}
	// Destructora
	virtual ~Image() {}
	// Inicializa el componente
	void initComponent() {
		tr_ = ent_->getComponent<Transform>(_TRANSFORM);
		assert( tr_ != nullptr );
	}
	// Dibuja en escena
	void render() {
		SDL_Rect dest = build_sdlrect(tr_->getPos(),tr_->getW(),tr_->getH());
		tex_->render(dest, tr_->getR());
	}

};