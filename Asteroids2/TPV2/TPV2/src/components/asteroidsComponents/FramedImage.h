#pragma once
#include "../../sdlutils/Texture.h"
#include "../../ecs/Manager.h"

struct FramedImage: public Component {
private:
//    // Consulta las caracteristicas fisicas
//	Transform* tr_; 
    // Imagen a rederizar
	//Texture* tex_;
    // Frame width
    int fw;
    // Frame height
    int fh; 
    int numCols;
    int numRows;
    int currentframe;
    int currentTime;
public:
    // Identificador
    constexpr static cmpId_type id = _FRAMEDIMAGE;
	// Constructora
    //FramedImage(Texture* tex, int fwidth, int fheight, int numRows = 1, int numCols = 1) : tex_(tex), fw(fwidth), 
    //           fh(fheight), numCols(numCols), numRows(numRows), currentframe(0) {};
	FramedImage(int fwidth, int fheight, int numRows = 1, int numCols = 1) : fw(fwidth),
		fh(fheight), numCols(numCols), numRows(numRows), currentframe(0) {};
	// Destructora
    virtual ~FramedImage() {/* _free();*/ }
    // Libera puntero a tex_
    /*   void _free() {
        tex_ = nullptr;
    }*/
   
    // Devuelve el numero de columnas
    //inline int getNumCols() const { return numCols; };

    //// Devuelve la textura
    //inline Texture* getTexture() const { return tex_; };
};