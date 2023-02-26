#pragma once
#include "../utils/Vector2D.h"
#include "../ecs/Component.h"

class Transform: public Component {
public:
	// Constructora
	Transform(Vector2D pos, Vector2D vel, float w, float h, float r){
		 position_ = pos; 
		 velocity_ = vel;
		 width_ = w;
		 height_= h;
		 rotation_ = r;
	}
	void setPos(Vector2D p) {
		position_ = p;
	}
	void setVel(Vector2D v) {
		velocity_ = v;
	}
	void changeRot(float r) {
		rotation_ += r;

	}
	// Destructora
	virtual ~Transform() { }
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
	virtual void update() {
		position_ = position_ + velocity_;
		//cout << position_ <<" velocity: "<< velocity_<< endl;

	}
private:
	Vector2D position_, velocity_;
	float width_, height_, rotation_;
};