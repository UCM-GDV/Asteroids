#pragma once
#include "../../sdlutils/Texture.h"

struct FramedImage: public Component {
private:
	//alto y ancho del frame
    int fw, fh; 
	//numero de filas y columnas de la animacion
    int numCols, numRows;
	//numero actual del frame
    int currentframe;
public:
    // Identificador
    constexpr static cmpId_type id = _FRAMEDIMAGE;
	// Constructora
	FramedImage(int fwidth, int fheight, int numRows = 1, int numCols = 1) : fw(fwidth),
		fh(fheight), numCols(numCols), numRows(numRows), currentframe(0) {};
	// Destructora
    virtual ~FramedImage() {}
	// Devuelve el ancho del frame
    inline int getFrameWidth() const { return fw; };
    // Devuelve el alto del frame
    inline int getFrameHeight() const { return fh; };
	// Devuelve el numero de columnas
	inline int getNumCols() const { return numCols; };
	// Devuelve el numero de filas
    inline int getNumRows() const { return numRows; };
	// Devuelve el frame actual
    inline int getCurrentFrame() const { return currentframe; };
	// Establece el ancho del frame
	inline void setFrameWidth(int fw_) { fw = fw_; };
	// Establece el alto del frame
	inline void setFrameHeight(int fh_) { fh = fh_; };
	// Establece el numero de columnas
	inline void setNumCols(int nCols_) { numCols = nCols_; };
	// Establece el numero de filas
	inline void setNumRows(int nRows_) { numRows = nRows_; };
	// Establece el frame actual
	inline void setCurrentFrame(int frame_) { currentframe = frame_; };
};