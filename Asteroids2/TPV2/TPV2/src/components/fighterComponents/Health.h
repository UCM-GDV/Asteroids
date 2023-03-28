#pragma once 

struct Health : public Component {
private:
	//numero de vidas
	int lives;
public:
	// Identificador
	constexpr static cmpId_type id = _HEALTH;
	// Constructora
	Health(int lives_) : lives(lives_) {}
	//devuelve las vidas
	int getlife() { return lives; }
	//cambia las vidas al numero indicado
	void setlife(int num) { lives = num; }
	//decrementa las vidas
	void decreaseLives() { lives--; }
};
