#pragma once
#include <cassert>
#include <math.h>
#include "../../ecs/Manager.h"

struct Generations : public Component {
private:
	int numGen;
public:
    // Identificador
    constexpr static cmpId_type id = _GENERATIONS;
	// Constructora
	Generations(int gen_) : numGen(gen_) {}
	// Destructora
	virtual ~Generations() {}
	// Inicializa el componente
	//void initComponent() {}
	// Cambia la generacion del componente
	inline void setGeneration(int gen_) { numGen = gen_; }
	// Devuelve la generacion del componente
	inline int getGenerations() { return numGen; }
};