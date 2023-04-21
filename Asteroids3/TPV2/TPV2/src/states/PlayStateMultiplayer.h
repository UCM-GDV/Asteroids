#pragma once
#include "../ecs/Manager.h"
// Sistemas
#include "../systems/BulletSystem.h"
#include "../systems/CollisionsSystem.h"
#include "../systems/FighterSystem.h"
#include "../systems/NetWorkSystem.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/RenderSystem.h"
#include "../sdlutils/InputHandler.h"
#include "../systems/NetWorkSystem.h"
class PlayStateMultiPlayer : public Manager {
private:
    FighterSystem* fighterSys_;
    GameCtrlSystem* gameCtrlSys_;
    RenderSystem* renderSys_;
    NetworkSystem* networkSys_;

    string ip;
public:
	// Constructora
	PlayStateMultiPlayer();
	// Destructora
	~PlayStateMultiPlayer();

    // Devuelve la ip
    inline string getIp() { return ip; }
    // Establece la ip
    inline void setIp(string ip_) { ip = ip_; }

    // UI
    Entity* hostButton;
    Entity* clientButton;
    Entity* enterButton;
    Entity* nameTextBox;
    Entity* waitingText;
    Entity* ipTextBox;

    void deActivateSELECTHUD();
    void deActivateNAMEHUD();
    void deActivateIPHUD();
    void createHostButton();
    void createClientButton();
    void createEnterButton(bool player);
    void createNameTextBox();
    void createWaitingTextBox();
    void createIpTextBox();

    void selectButtonAction(bool player);
    void hostButtonNameAction();
    void clientButtonIPAction();
};