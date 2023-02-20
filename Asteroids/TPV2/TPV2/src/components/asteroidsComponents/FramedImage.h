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
    //SDL_Renderer* renderer;
    //int w;
    //int h;
    int fw; // Frame width
    int fh; // Frame height
    int numCols;
    int numRows;
    int currentframe;
public:
	// Constructora
	FramedImage(Texture* tex) : tr_(nullptr), tex_(tex), fw(0), fh(0), numCols(1), numRows(0), currentframe(0){};
    FramedImage(Texture* tex, int fwidth, int fheight, int numRows = 1, int numCols = 1) : tex_(tex), fw(fwidth), 
               fh(fheight), numCols(numCols), numRows(numRows), currentframe(0) {};
	// Destructora
    virtual ~FramedImage() { _free(); }
    void _free() {
        delete tex_;
        tex_ = nullptr;
       // w = h = 0;
    }
    // Inicializa el componente
    void initComponent() {
        tr_ = ent_->getComponent<Transform>(_TRANSFORM);
        assert(tr_ != nullptr);
    }
    // Dibuja en escena
    void render() {
        SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
        SDL_Rect src;
        src.x = (currentframe % numCols) * fw;
        src.y = (currentframe / numCols) * fh;
        src.w = fw;
        src.h = fh;
        tex_->render(src, dest);
    }
    void update() {
        currentframe = (currentframe + 1) % (numCols* numRows - 1);
    }
    // Returns the width of the texture
    //int getW() const { return w; };
    // Returns the height of the texture
    //int getH() const { return h; };
    // Returns the number of columns
    uint getNumCols() const { return numCols; };
    // Returns the texture pointer
    Texture* getTexture() const { return tex_; };
}; 
#endif // !FRAMED_IMAGE_H_