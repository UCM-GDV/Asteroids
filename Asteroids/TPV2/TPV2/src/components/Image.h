#pragma once
#ifndef IMAGE_H_
#define IMAGE_H_
#include "../sdlutils/Texture.h"
#include "Transform.h" 

class Image: public Component {
public:
	// Constructora
	Image(Texture* tex) : tr_(nullptr), tex_(tex) { }
	// Destructora
	virtual ~Image() { }
	// Inicializa el componente
	void initComponent() override;
	// Dibuja
	void render() override;
	// Inicializa el componente
	void initComponent() {
		//tr_ = ent_->getComponent<Transform>(_TRANSFORM);
		//assert( tr_ != nullptr );
	}
	// Dibuja en escena
	void render() {
		SDL_Rect dest = build_sdlrect(tr_->getPos(),tr_->getW(),tr_->getH());
		tex_->render(dest, tr_->getR());
	}
private:
	Transform* tr_; // Consulta las caracteristicas fisicas
	Texture* tex_;	// Imagen a rederizar
};
#endif