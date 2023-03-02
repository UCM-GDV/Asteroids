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
		Generations(int gen_);
		void initComponent();
		inline void setGeneration(int gen_) { numGen = gen_; }
		inline int getGenerations() { return numGen; }
		inline void decreaseGeneration() { --numGen; }
		virtual ~Generations();

};