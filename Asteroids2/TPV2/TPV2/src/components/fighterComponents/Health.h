#pragma once 

struct Health : public Component {
private:
	int lives;/*
	Texture* texture;*/
public:
	// Identificador
	constexpr static cmpId_type id = _HEALTH;
	//// Constructora
	Health(int lives_) : lives(lives_) {}
	//// Destructora
	//   virtual ~Health();
	int getlife() { return lives; }
	void setlife(int num) { lives = num; }
	void decreaseLives() { lives--; }
};
