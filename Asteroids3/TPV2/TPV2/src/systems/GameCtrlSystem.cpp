#include "GameCtrlSystem.h"
#include "../ecs/Manager.h"
#include "../game/GameStateMachine.h"
#include "../states/MainMenuState.h"
#include "../states/PauseState.h"
#include "../states/PlayState.h"
#include "../states/EndState.h"
#include "../states/MainMenuState.h"
#include "../states/PlayStateMultiplayer.h"

// Constructoras
GameCtrlSystem::GameCtrlSystem() : fighterHealth(nullptr), fighterHealth1(nullptr), fighterHealth2(nullptr), name("") {}
GameCtrlSystem::GameCtrlSystem(int state_) : state(state_), fighterHealth(nullptr), fighterHealth1(nullptr), fighterHealth2(nullptr), name("") {}

// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void GameCtrlSystem::receive(const Message& m) {
    switch (m.id) {
    case _m_FIGTHER_ASTEROID_COLLIDED: onCollision_FighterAsteroid(); break;
    case _m_ASTEROIDS_EXTINCTION: onAsteroidsExtinction(); break;
    case _m_CHANGE_STATE: onChangeState();  break;
    case _m_FIGHTER_BULLET_COLLIDED: case _m_FIGHTER_FIGHTER_COLLIDED: onCollision_Multiplayer(m.fighter_bullet_coll.fighterHealth); break;
    case _m_RESET_MULTIPLAYER_STATE: GameStateMachine::instance()->changeState(new PlayStateMultiPlayer()); break;
    default: break;
    }
}

// Inicializar el sistema, etc.
void GameCtrlSystem::initSystem() {
    if (state == 1) {
		fighterHealth = mngr_->getSystem<FighterSystem>()->getFighterHealth();
		assert(fighterHealth != nullptr);
    }
}

// Si el juego no está parado y el jugador pulsa SDLK_SPACE cambia el estado
// como en la práctica 1, etc.
//  Tiene que enviar mensajes correspondientes cuando
// empieza una ronda o cuando empieza una nueva partida.
void GameCtrlSystem::update() {
    if (InputHandler::instance()->closeWindowEvent()) {
        quit();
    }

    if (InputHandler::instance()->keyDownEvent()) {
        if (state == 0 || state == 1 || state == 2 || state == 5) {
            if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
                // Si esta en PlayState
                if (state == 1) {
                    GameStateMachine::instance()->pushState(new PauseState());
                }
                // Si esta en PauseState
                else if (state == 0) {
                    GameStateMachine::instance()->popState();
                    Message m;
                    m.id = _m_ROUND_STARTED;
                    GameStateMachine::instance()->currentState()->send(m);
                }
                // Si esta en EndState
                else if (state == 2) {
                    GameStateMachine::instance()->changeState(new PauseState());
                }
                // Si esta en EndState del modo multijugador
                else if (state == 5) {
					GameStateMachine::instance()->popState();
                }
            }
        }
        // Si esta en PlayStateMultiplayer
        else if (state == 4) {
			Entity* nameEnt = static_cast<PlayStateMultiPlayer*>(mngr_)->nameTextBox;
			Entity* ipEnt = static_cast<PlayStateMultiPlayer*>(mngr_)->ipTextBox;

			// Si existe nameTextBox...
			if (nameEnt != nullptr) {
				delete mngr_->UITextures_[nameEnt];
				addCharacter();
				addSpaces(name, nameWithSpaces);
				mngr_->UITextures_[nameEnt] = new Texture(SDLUtils::instance()->renderer(), nameWithSpaces, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(COLOR_BLACK), build_sdlcolor(COLOR_WHITE));
			}
			// Si existe ipTextBox
			if (ipEnt != nullptr) {
				delete mngr_->UITextures_[ipEnt];
				addNumberOrDot();
				addSpaces(ip, ipWithSpaces);
				mngr_->UITextures_[ipEnt] = new Texture(SDLUtils::instance()->renderer(), ipWithSpaces, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(COLOR_BLACK), build_sdlcolor(COLOR_WHITE));
			}

			if (InputHandler::instance()->isKeyDown(SDLK_RETURN)) {
				Entity* enterEnt = static_cast<PlayStateMultiPlayer*>(mngr_)->enterButton;
				if (enterEnt != nullptr) {
					// Llama a la funcion
					mngr_->getComponent<Callback>(enterEnt)->callback();
				}
			}
        }
    }

    // Si se ha hecho clic izquierdo
    if (InputHandler::instance()->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT)) {
        // Si esta en MainMenuState
        if (state == -1 || state == 4) {
            // Comprueba si la posicion del cursor esta dentro de la imagen de algun boton
            vector<Entity*> buttons = mngr_->getEntities(_grp_UI);
            for (int i = 0; i < buttons.size(); ++i) {
                pair<Sint32, Sint32> mousePos = InputHandler::instance()->getMousePos();
                SDL_Point mousePoint = { (int)mousePos.first, (int)mousePos.second };
                SDL_Rect* buttonRect = &mngr_->getComponent<Transform>(buttons[i])->getRect();

                if (SDL_PointInRect(&mousePoint, buttonRect)) {
					// Llama a la funcion
                    Callback* cb = mngr_->getComponent<Callback>(buttons[i]);
                    if (cb != nullptr) {
                        cb->callback();
                    }
                }
            }
        }
    }

    InputHandler::instance()->refresh();
}

// Para gestionar el mensaje de que ha habido un choque entre el fighter y un
// un asteroide. Tiene que avisar que ha acabado la ronda, quitar una vida
// al fighter, y si no hay más vidas avisar que ha acabado el juego (y quien
// es el ganador).
void GameCtrlSystem::onCollision_FighterAsteroid() {
    fighterHealth->decreaseLives();
    sdlutils().soundEffects().at("explosion").play();

	Message m;
    if (fighterHealth->getlife() <= 0) {
		m.id = _m_ONDEFEAT;
        GameStateMachine::instance()->pushState(new EndState(GAME_OVER_LOSE_TEXT));
    }
    else {
		m.id = _m_ROUND_FINISHED;
        GameStateMachine::instance()->pushState(new PauseState());
    }
    mngr_->send(m);
}

// Si hay colision entre fighter y bullet o fighter y fighter en el modo multijugador
// Gestiona las vidas y si alguno llega a 0, se coloca el endState
void GameCtrlSystem::onCollision_Multiplayer(int fighterHealth) {
	//repoduce sonido de la explosion
	sdlutils().soundEffects().at("explosion").play();

	// Actualiza las vidas
	if (fighterHealth == 1) fighterHealth1->decreaseLives();
	else if (fighterHealth == 2) fighterHealth2->decreaseLives();
	else {
		fighterHealth1->decreaseLives();
		fighterHealth2->decreaseLives();
	}

	int health1 = fighterHealth1->getlife();
	int health2 = fighterHealth2->getlife();
	if (health1 <= 0 || health2 <= 0) {
		GameStateMachine::instance()->popState();
		GameStateMachine::instance()->pushState(new MainMenuState());
		NetworkSystem* net = mngr_->getSystem<NetworkSystem>();
		if (net->getServer()) {
			//si eres servidor
			//si ganas tu
			if (health1 <= 0) winner = net->othername;
			//si gana el otro
			else winner = name;
		}
		else {
			//si eres cliente 
			//si gana el otro
			if (health1 <= 0) winner = name;
			//si ganas tu
			else  winner = net->othername;
		}

		GameStateMachine::instance()->pushState(new EndState(winner));
	}
}

// Para gestionar el mensaje de que no hay más asteroides. Tiene que avisar que
// ha acabado la ronda y además que ha acabado el juego (y quien es el ganador)
void GameCtrlSystem::onAsteroidsExtinction() {
    Message m;
    m.id = _m_ONVICTORY;
    mngr_->send(m);
    GameStateMachine::instance()->pushState(new EndState(GAME_OVER_WIN_TEXT));
}

// Cambio del estado de seleccion al de juego multijugador
void GameCtrlSystem::onChangeState() {
	state = 3;

	// Coge las referencias
	fighterHealth1 = mngr_->getSystem<FighterSystem>()->getFighterHealth1();
	fighterHealth2 = mngr_->getSystem<FighterSystem>()->getFighterHealth2();
	(mngr_->getSystem<NetworkSystem>()->getServer()) ? fighterHealth = fighterHealth1 : fighterHealth = fighterHealth2;
}

// Anade caracteres en la textura del nombre
void GameCtrlSystem::addCharacter() {
    if (name.size() < 10) {
        string c = "";
         if (InputHandler::instance()->isKeyDown(SDLK_e)) c = "e";
        else if (InputHandler::instance()->isKeyDown(SDLK_a)) c = "a";
        else if (InputHandler::instance()->isKeyDown(SDLK_o)) c = "o";
        else if (InputHandler::instance()->isKeyDown(SDLK_s)) c = "s";
        else if (InputHandler::instance()->isKeyDown(SDLK_r)) c = "r";
        else if (InputHandler::instance()->isKeyDown(SDLK_n)) c = "n";
        else if (InputHandler::instance()->isKeyDown(SDLK_i)) c = "i";
        else if (InputHandler::instance()->isKeyDown(SDLK_d)) c = "d";
        else if (InputHandler::instance()->isKeyDown(SDLK_l)) c = "l";
        else if (InputHandler::instance()->isKeyDown(SDLK_c)) c = "c";
        else if (InputHandler::instance()->isKeyDown(SDLK_t)) c = "t";
        else if (InputHandler::instance()->isKeyDown(SDLK_u)) c = "u";
        else if (InputHandler::instance()->isKeyDown(SDLK_m)) c = "m";
        else if (InputHandler::instance()->isKeyDown(SDLK_p)) c = "p";
        else if (InputHandler::instance()->isKeyDown(SDLK_b)) c = "b";
        else if (InputHandler::instance()->isKeyDown(SDLK_g)) c = "g";
        else if (InputHandler::instance()->isKeyDown(SDLK_f)) c = "f";
        else if (InputHandler::instance()->isKeyDown(SDLK_h)) c = "h";
        else if (InputHandler::instance()->isKeyDown(SDLK_j)) c = "j";
        else if (InputHandler::instance()->isKeyDown(SDLK_k)) c = "k";
        else if (InputHandler::instance()->isKeyDown(SDLK_q)) c = "q";
        else if (InputHandler::instance()->isKeyDown(SDLK_v)) c = "v";
        else if (InputHandler::instance()->isKeyDown(SDLK_w)) c = "w";
        else if (InputHandler::instance()->isKeyDown(SDLK_x)) c = "x";
        else if (InputHandler::instance()->isKeyDown(SDLK_y)) c = "y";
        else if (InputHandler::instance()->isKeyDown(SDLK_z)) c = "z";
       
        name += c;
    }
    if (InputHandler::instance()->isKeyDown(SDLK_BACKSPACE)) {
        if (name.size() > 0) name.pop_back();
    };
   
}

// Anade espacios para que se vea bien
void GameCtrlSystem::addSpaces(string text, string& textWithSpaces) {
    textWithSpaces = text;
    for (int i = text.size(); i < 26; ++i) {
        textWithSpaces += " ";
    }
}

// Anade numeros
void GameCtrlSystem::addNumberOrDot() {
    string n = "";
    if (InputHandler::instance()->isKeyDown(SDLK_0)) n = "0";
    else if (InputHandler::instance()->isKeyDown(SDLK_1)) n = "1";
    else if (InputHandler::instance()->isKeyDown(SDLK_2)) n = "2";
    else if (InputHandler::instance()->isKeyDown(SDLK_3)) n = "3";
    else if (InputHandler::instance()->isKeyDown(SDLK_4)) n = "4";
    else if (InputHandler::instance()->isKeyDown(SDLK_5)) n = "5";
    else if (InputHandler::instance()->isKeyDown(SDLK_6)) n = "6";
    else if (InputHandler::instance()->isKeyDown(SDLK_7)) n = "7";
    else if (InputHandler::instance()->isKeyDown(SDLK_8)) n = "8";
    else if (InputHandler::instance()->isKeyDown(SDLK_9)) n = "9";
    else if (InputHandler::instance()->isKeyDown(SDLK_PERIOD)) n = ".";
    else if (InputHandler::instance()->isKeyDown(SDLK_BACKSPACE)) {
        if (ip.size() > 0) ip.pop_back();
    };

    ip += n;
}

// Cierra el programa
void GameCtrlSystem::quit() {
    if (state == 3) {
		Message m;
		m.id = _m_DISCONNECT;
		mngr_->send(m);
    }
    GameStateMachine::instance()->quitGame();
}