#pragma once
#include "../../game/Game.h"
#include "../../sdlutils/Texture.h"
#include "../Transform.h" 
#include "../../ecs/Entity.h"

class FramedImage: public Component{
private:
    // Consulta las caracteristicas fisicas
	Transform* tr_; 
    // Imagen a rederizar
	Texture* tex_;	
    // Frame width
    int fw;
    // Frame height
    int fh; 
    int numCols;
    int numRows;
    int currentframe;
    int currentTime;
public:
	// Constructora
    FramedImage(Texture* tex, int fwidth, int fheight, int numRows = 1, int numCols = 1) : tex_(tex), fw(fwidth), 
               fh(fheight), numCols(numCols), numRows(numRows), currentframe(0) {};
	// Destructora
    virtual ~FramedImage() { _free(); }
    // Libera puntero a tex_
    void _free() {
        tex_ = nullptr;
    }
    // Inicializa el componente
    void initComponent() {
        tr_ = ent_->getComponent<Transform>(_TRANSFORM);
        assert(tr_ != nullptr);
    }
    // Acutlualiza el currentframe
    void update() {
        currentframe = (currentframe + 1) % (numCols * numRows - 1);
        currentTime = 0;
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
    
    // Devuelve el numero de columnas
    inline int getNumCols() const { return numCols; };
    // Devuelve la textura
    inline Texture* getTexture() const { return tex_; };
};