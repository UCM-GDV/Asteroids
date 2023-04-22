#include "GameCtrlSystem.h"
#include "../ecs/Manager.h"
#include "../game/GameStateMachine.h"
#include "../states/PauseState.h"
#include "../states/PlayState.h"
#include "../states/EndState.h"
#include "../states/MainMenuState.h"
#include "../states/PlayStateMultiplayer.h"

// Constructoras
GameCtrlSystem::GameCtrlSystem() : fighterHealth(nullptr), name("") {}
GameCtrlSystem::GameCtrlSystem(int state_) : state(state_), fighterHealth(nullptr), name("") {}

// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
void GameCtrlSystem::receive(const Message& m) {
    switch (m.id) {
        // colision asteroide con fighter
    case _m_FIGTHER_ASTEROID_COLLIDED: onCollision_FighterAsteroid(); break;
    case _m_ASTEROIDS_EXTINCTION: onAsteroidsExtinction(); break;
    case _m_CHANGE_STATE: onChangeState();  break;
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
    
    if (InputHandler::instance()->keyDownEvent()) {
        if (state == 0 || state == 1 || state == 2) {
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
	Message m;
    if (fighterHealth->getlife() <= 0) {
		m.id = _m_ONDEFEAT;
        GameStateMachine::instance()->pushState(new EndState(2));
    }
    else {
		m.id = _m_ROUND_FINISHED;
        GameStateMachine::instance()->pushState(new PauseState());
    }
    mngr_->send(m);
}

// Para gestionar el mensaje de que no hay más asteroides. Tiene que avisar que
// ha acabado la ronda y además que ha acabado el juego (y quien es el ganador)
void GameCtrlSystem::onAsteroidsExtinction() {
    Message m;
    m.id = _m_ONVICTORY;
    mngr_->send(m);
    GameStateMachine::instance()->pushState(new EndState(1));
}

// Devuelve si el cursor esta encima de un boton o no
bool GameCtrlSystem::isOver(Entity* button, std::pair<Sint32, Sint32> mousePos) const {
    Transform* buttonTransform = mngr_->getComponent<Transform>(button);
    if (buttonTransform != nullptr) {
        Vector2D position = buttonTransform->getPos();
        return mousePos.first > position.getX()
            && mousePos.first < position.getX() + buttonTransform->getW()
            && mousePos.second > position.getY()
            && mousePos.second < position.getY() + buttonTransform->getH();
    }
    else return false;
}

// Anade caracteres en la textura del nombre
void GameCtrlSystem::addCharacter() {
    string c = "";
    if (InputHandler::instance()->isKeyDown(SDLK_a)) c = "a";
    if (InputHandler::instance()->isKeyDown(SDLK_b)) c = "b";
    if (InputHandler::instance()->isKeyDown(SDLK_c)) c = "c";
    if (InputHandler::instance()->isKeyDown(SDLK_d)) c = "d";
    if (InputHandler::instance()->isKeyDown(SDLK_e)) c = "e";
    if (InputHandler::instance()->isKeyDown(SDLK_f)) c = "f";
    if (InputHandler::instance()->isKeyDown(SDLK_g)) c = "g";
    if (InputHandler::instance()->isKeyDown(SDLK_h)) c = "h";
    if (InputHandler::instance()->isKeyDown(SDLK_i)) c = "i";
    if (InputHandler::instance()->isKeyDown(SDLK_j)) c = "j";
    if (InputHandler::instance()->isKeyDown(SDLK_k)) c = "k";
    if (InputHandler::instance()->isKeyDown(SDLK_l)) c = "l";
    if (InputHandler::instance()->isKeyDown(SDLK_m)) c = "m";
    if (InputHandler::instance()->isKeyDown(SDLK_n)) c = "n";
    if (InputHandler::instance()->isKeyDown(SDLK_o)) c = "o";
    if (InputHandler::instance()->isKeyDown(SDLK_p)) c = "p";
    if (InputHandler::instance()->isKeyDown(SDLK_q)) c = "q";
    if (InputHandler::instance()->isKeyDown(SDLK_r)) c = "r";
    if (InputHandler::instance()->isKeyDown(SDLK_s)) c = "s";
    if (InputHandler::instance()->isKeyDown(SDLK_t)) c = "t";
    if (InputHandler::instance()->isKeyDown(SDLK_u)) c = "u";
    if (InputHandler::instance()->isKeyDown(SDLK_v)) c = "v";
    if (InputHandler::instance()->isKeyDown(SDLK_w)) c = "w";
    if (InputHandler::instance()->isKeyDown(SDLK_x)) c = "x";
    if (InputHandler::instance()->isKeyDown(SDLK_y)) c = "y";
    if (InputHandler::instance()->isKeyDown(SDLK_z)) c = "z";
    name += c;
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
    if (InputHandler::instance()->isKeyDown(SDLK_1)) n = "1";
    if (InputHandler::instance()->isKeyDown(SDLK_2)) n = "2";
    if (InputHandler::instance()->isKeyDown(SDLK_3)) n = "3";
    if (InputHandler::instance()->isKeyDown(SDLK_4)) n = "4";
    if (InputHandler::instance()->isKeyDown(SDLK_5)) n = "5";
    if (InputHandler::instance()->isKeyDown(SDLK_6)) n = "6";
    if (InputHandler::instance()->isKeyDown(SDLK_7)) n = "7";
    if (InputHandler::instance()->isKeyDown(SDLK_8)) n = "8";
    if (InputHandler::instance()->isKeyDown(SDLK_9)) n = "9";
    if (InputHandler::instance()->isKeyDown(SDLK_PERIOD)) n = ".";

    ip += n;
}

void GameCtrlSystem::onChangeState() {
    // Cambia del modo de seleccion al juego
	state = 3;  
    // Coge las referencias
    (mngr_->getSystem<NetworkSystem>()->getServer()) ? fighterHealth = fighterHealth1 : fighterHealth = fighterHealth2;
}