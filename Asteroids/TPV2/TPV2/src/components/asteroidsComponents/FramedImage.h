#pragma once
#ifndef FRAMED_IMAGE_H_
#define FRAMED_IMAGE_H_
#include "../../game/Game.h"
#include "../../sdlutils/Texture.h"
#include "../Transform.h" 
#include "../../ecs/Entity.h"

class FramedImage: public Component{
private:
	Transform* tr_; // Consulta las caracteristicas fisicas
	Texture* tex_;	// Imagen a rederizar
    SDL_Renderer* renderer = nullptr;
    uint w = 0;
    uint h = 0;
    uint fw = 0; // Frame width
    uint fh = 0; // Frame height
    uint numCols = 1;
    uint numRows = 1;
public:
	// Constructora
	FramedImage(Texture* tex) : tr_(nullptr), tex_(tex) {};
	FramedImage(SDL_Renderer* r, string filename, uint numRows = 1, uint numCols = 1);
	// Destructora
    virtual ~FramedImage() { _free(); }
    void _free() {
        delete tex_;
        tex_ = nullptr;
        w = h = 0;
    }
    // Inicializa el componente
    void initComponent() {
        tr_ = ent_->getComponent<Transform>(_TRANSFORM);
        assert(tr_ != nullptr);
    }
    // Dibuja en escena
    void render() {
        SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
        tex_->render(dest, tr_->getR());
    }
    // Returns the width of the texture
    int getW() const { return w; };
    // Returns the height of the texture
    int getH() const { return h; };
    // Returns the number of columns
    uint getNumCols() const { return numCols; };
    // Returns the texture pointer
    Texture* getTexture() const { return tex_; };
}; 
#endif // !FRAMED_IMAGE_H_