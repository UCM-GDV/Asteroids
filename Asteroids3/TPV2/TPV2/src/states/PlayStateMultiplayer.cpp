#include "./PlayStateMultiplayer.h"

// Constructora
PlayStateMultiPlayer::PlayStateMultiPlayer() : Manager(), hostButton(nullptr), clientButton(nullptr), enterButton(nullptr), nameTextBox(nullptr), waitingText(nullptr), ipTextBox(nullptr) {
	// SISTEMAS
    networkSys_ = addSystem<NetworkSystem>();
    fighterSys_ = addSystem<FighterSystem>(3);
    gameCtrlSys_ = addSystem<GameCtrlSystem>(3);
	addSystem<BulletSystem>();
	addSystem<CollisionsSystem>();
    renderSys_ = addSystem<RenderSystem>(3);

    createHostButton();
    createClientButton();
}

// Destructora
PlayStateMultiPlayer::~PlayStateMultiPlayer() {
    SDLNet_Quit();
}

void PlayStateMultiPlayer::deActivateSELECTHUD() {
    // QUITA LOS BOTONES DE HOST Y CLIENT
    hostButton->setAlive(false);
    clientButton->setAlive(false);
}

void PlayStateMultiPlayer::deActivateNAMEHUD() {
    // QUITA EL BOTON DE NAME Y ENTER
    nameTextBox->setAlive(false);
    enterButton->setAlive(false);
}

void PlayStateMultiPlayer::deActivateIPHUD() {
    // QUITA LOS BOTONES DE IP Y ENTER
    ipTextBox->setAlive(false);
    enterButton->setAlive(false);
}

void PlayStateMultiPlayer::createHostButton() {
    hostButton = new Entity(_grp_BUTTONS);
    hostButton->setContext(this);
    addComponent<Transform>(hostButton, ONEPLAYER_BUTTON_POSITION, VECTOR_ZERO, BUTTON_WIDTH, BUTTON_HEIGHT, 0);
    textTextures_[hostButton] = new Texture(SDLUtils::instance()->renderer(), HOST_TEXT, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(COLOR_BLACK), build_sdlcolor(COLOR_WHITE));
    addComponent<Callback>(hostButton, [&]() { selectButtonAction(false); });
    addEntity(hostButton, _grp_BUTTONS);
}

void PlayStateMultiPlayer::createClientButton() {
    clientButton = new Entity(_grp_BUTTONS);
    clientButton->setContext(this);
    addComponent<Transform>(clientButton, MULTIPLAYER_BUTTON_POSITION, VECTOR_ZERO, BUTTON_WIDTH, BUTTON_HEIGHT, 0);
    textTextures_[clientButton] = new Texture(SDLUtils::instance()->renderer(), CLIENT_TEXT, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(COLOR_BLACK), build_sdlcolor(COLOR_WHITE));
    addComponent<Callback>(clientButton, [&]() { selectButtonAction(true); });
    addEntity(clientButton, _grp_BUTTONS);
}

void PlayStateMultiPlayer::createEnterButton(bool player) {
    enterButton = new Entity(_grp_BUTTONS);
    enterButton->setContext(this);
    addComponent<Transform>(enterButton, MULTIPLAYER_BUTTON_POSITION, VECTOR_ZERO, BUTTON_WIDTH, BUTTON_HEIGHT, 0);
    textTextures_[enterButton] = new Texture(SDLUtils::instance()->renderer(), ENTER_TEXT, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(COLOR_WHITE), build_sdlcolor(COLOR_RED));

    // !player = JUGADOR 1 || player = JUGADOR 2
    (!player) ? addComponent<Callback>(enterButton, [&]() { hostButtonNameAction(); }) : addComponent<Callback>(enterButton, [&]() { clientButtonIPAction(); });

    addEntity(enterButton, _grp_BUTTONS);
}

void PlayStateMultiPlayer::createNameTextBox() {
    nameTextBox = new Entity(_grp_TEXTBOXS);
    nameTextBox->setContext(this);
    addComponent<Transform>(nameTextBox, ONEPLAYER_BUTTON_POSITION, VECTOR_ZERO, BUTTON_WIDTH, BUTTON_HEIGHT, 0);
    textTextures_[nameTextBox] = new Texture(SDLUtils::instance()->renderer(), NAME_TEXT_BOX, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(COLOR_BLACK), build_sdlcolor(COLOR_WHITE));
    addEntity(nameTextBox, _grp_TEXTBOXS);
}

void PlayStateMultiPlayer::createWaitingTextBox() {
    waitingText = new Entity(_grp_MESSAGES);
    waitingText->setContext(this);
    addComponent<Transform>(waitingText, ONEPLAYER_BUTTON_POSITION, VECTOR_ZERO, BUTTON_WIDTH, BUTTON_HEIGHT, 0);
    textTextures_[waitingText] = new Texture(SDLUtils::instance()->renderer(), WAITING_TEXT, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(COLOR_BLACK), build_sdlcolor(COLOR_WHITE));
    addEntity(waitingText, _grp_MESSAGES);
}

void PlayStateMultiPlayer::createIpTextBox() {
    ipTextBox = new Entity(_grp_TEXTBOXS);
    ipTextBox->setContext(this);
    addComponent<Transform>(ipTextBox, ONEPLAYER_BUTTON_POSITION, VECTOR_ZERO, BUTTON_WIDTH, BUTTON_HEIGHT, 0);
    textTextures_[ipTextBox] = new Texture(SDLUtils::instance()->renderer(), IP_TEXT, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(COLOR_BLACK), build_sdlcolor(COLOR_WHITE));
    addEntity(ipTextBox, _grp_TEXTBOXS);
}

void PlayStateMultiPlayer::selectButtonAction(bool player) {
    deActivateSELECTHUD();
    createNameTextBox();
    createEnterButton(player);
}

void PlayStateMultiPlayer::hostButtonNameAction() {
    deActivateNAMEHUD();
    createWaitingTextBox();

    networkSys_->server();
}

void PlayStateMultiPlayer::clientButtonIPAction() {
    // Reescribe el callback del boton de enter
    getComponent<Callback>(enterButton)->setCallback([&]() {
        deActivateIPHUD();
        // TODO ---------------------------------------
        const char* ip = gameCtrlSys_->getIp().c_str();
        cout << ip << endl;
        // --------------------------------------------

        networkSys_->client(ip);
    });

    nameTextBox->setAlive(false);
    createIpTextBox();
}