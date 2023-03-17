//#pragma once
//#include <cassert>
//#include <math.h>
//#include "../Transform.h" 
//#include "../../ecs/Entity.h"
//#include "../../ecs/Component.h"
//#include "../../sdlutils/SDLUtils.h"
//#include "../../sdlutils/InputHandler.h"
//#include "../../components/fighterComponents/Gun.h"

//class FighterControl : public Component {
//	private:
//		// Coge el componente transofrm
//		Transform* transform;
//	public:
//      // Identificador
//		constexpr static cmpId_type id = _FIGHTERCONTROL;
//		// Constructora
//		FighterControl();
//		// Destructora
//		virtual ~FighterControl();
//		// Inicializa el componente
//		void initComponent();
//		// Rota el fighter
//		void rotate(float r_);
//		// Acelera el fighter
//		void acelerate();
//		// Recoge el input del jugador
//		virtual void handleEvent(SDL_Event event);
//		// Convierte de grados a radianes
//		float degreesToRadians(float degree_);
//};