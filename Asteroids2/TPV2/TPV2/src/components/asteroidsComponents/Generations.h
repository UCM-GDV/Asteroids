#pragma once
#include <cassert>
#include <math.h>
#include "../Transform.h" 
#include "../../ecs/Entity.h"
#include "../../ecs/Component.h"

class Generations : public Component {
private:
	int numGen;
	public:
		// Constructora
		Generations(int gen_);
		// Destructora
		 virtual ~Generations();
		// Inicializa el componente
		void initComponent();
		// Cambia la generacion del componente
		inline void setGeneration(int gen_) { numGen = gen_; }
		// Devuelve la generacion del componente
		inline int getGenerations() { return numGen; }
		// Decrementa la generacion
		inline void decreaseGeneration() { --numGen; }
		

};