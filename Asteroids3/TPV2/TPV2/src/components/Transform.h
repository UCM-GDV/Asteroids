#pragma once
#include "../utils/Vector2D.h"

struct Transform : public Component {
	// Identificador
	constexpr static cmpId_type id = _TRANSFORM;
	// Vectores de posicion y velocidad
	Vector2D position_, velocity_;
	// Ancho, alto y rotacion
	float width_, height_, rotation_;
	// Constructora
	Transform(Vector2D pos, Vector2D vel, float w, float h, float r) :
		position_(pos), velocity_(vel), width_(w), height_(h), rotation_(r) {};
	// Devuelve su rect
	inline SDL_Rect& getRect() {
		SDL_Rect rect;
		rect.x = position_.getX();
		rect.y = position_.getY();
		rect.w = width_;
		rect.h = height_;
		return rect;
	}
	// Devuelve su posicion
	inline Vector2D& getPos() { return position_; }
	// Devuelve su velocidad
	inline Vector2D& getVel() { return velocity_; }
	// Devuelve su ancho
	inline float getW() { return width_; }
	// Devuelve su altura
	inline float getH() { return height_; }
	// Devuelve su rotacion
	inline float getR() { return rotation_; }
	// Establece la posicion
	inline void setPos(Vector2D p) { position_ = p; }
	// Establece la velocidad
	inline void setVel(Vector2D v) { velocity_ = v; }
	// Establece la rotacion
	inline void setRot(int r) { rotation_ = r; }
	// Cambia la rotacion
	inline void changeRot(float r) { rotation_ += r; }
};