#include "./PlayStateMultiplayer.h"

// CONSTRUCTORA
PlayStateMultiPlayer::PlayStateMultiPlayer() : Manager(), hostButton(nullptr), clientButton(nullptr), enterButton(nullptr), nameTextBox(nullptr), waitingText(nullptr), ipTextBox(nullptr) {
	// SISTEMAS
    networkSys_ = addSystem<NetworkSystem>();
    renderSys_ = addSystem<RenderSystem>(4);
    gameCtrlSys_ = addSystem<GameCtrlSystem>(4);
    //CREA EL BOTON DEL HOST Y DEL CLIENTE 
    createHostButton();
    createClientButton();
}
 void PlayStateMultiPlayer::createsystems() {
     //CREA LOS SISTEMAS
     fighterSys_ = addSystem<FighterSystem>(3);
     addSystem<BulletSystem>(3);
     addSystem<CollisionsSystem>(3);
     //ANADE ENTIDAD CON LOS NOMBRES
     addName(name);
     //ENVIA MENSAJE PARA QUE SE CREE EL NOMBRE EN EL OTRO USUARIO
     networkSys_->sendname(name);
}
 void PlayStateMultiPlayer::addName(string name) {
     //CREA LA ENTIDAD DE LOS NOMBRES
     Entity* nametext = new Entity(_grp_UI);
     nametext->setContext(this);
     addComponent<Transform>(nametext, FIGHTER_1_POS, VECTOR_ZERO, NAME_WIDTH, NAME_HEIGHT, 0);
     UITextures_[nametext] = new Texture(SDLUtils::instance()->renderer(), name, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(COLOR_WHITE));
     addEntity(nametext, _grp_UI);
 }
// DESTRUCTORA
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
    ip = gameCtrlSys_->getIp();
    ipTextBox->setAlive(false);
    enterButton->setAlive(false);
}

void PlayStateMultiPlayer::createHostButton() {
    //ANADE LA ENTIDAD DEL BOTON HOST 
    hostButton = new Entity(_grp_UI);
    hostButton->setContext(this);
    addComponent<Transform>(hostButton, ONEPLAYER_BUTTON_POSITION, VECTOR_ZERO, BUTTON_WIDTH, BUTTON_HEIGHT, 0);
    UITextures_[hostButton] = new Texture(SDLUtils::instance()->renderer(), HOST_TEXT, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(COLOR_BLACK), build_sdlcolor(COLOR_WHITE));
    addComponent<Callback>(hostButton, [&]() { selectButtonAction(false); });
    addEntity(hostButton, _grp_UI);
}

void PlayStateMultiPlayer::createClientButton() {
    //ANADE LA ENTIDAD DEL BOTON CLIENTE
    clientButton = new Entity(_grp_UI);
    clientButton->setContext(this);
    addComponent<Transform>(clientButton, MULTIPLAYER_BUTTON_POSITION, VECTOR_ZERO, BUTTON_WIDTH, BUTTON_HEIGHT, 0);
    UITextures_[clientButton] = new Texture(SDLUtils::instance()->renderer(), CLIENT_TEXT, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(COLOR_BLACK), build_sdlcolor(COLOR_WHITE));
    addComponent<Callback>(clientButton, [&]() { selectButtonAction(true); });
    addEntity(clientButton, _grp_UI);
}

void PlayStateMultiPlayer::createEnterButton(bool player) {
    //CREA EL BOTON DE ENTER
    enterButton = new Entity(_grp_UI);
    enterButton->setContext(this);
    addComponent<Transform>(enterButton, MULTIPLAYER_BUTTON_POSITION, VECTOR_ZERO, BUTTON_WIDTH, BUTTON_HEIGHT, 0);
    UITextures_[enterButton] = new Texture(SDLUtils::instance()->renderer(), ENTER_TEXT, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(COLOR_WHITE), build_sdlcolor(COLOR_RED));

    // !player = JUGADOR 1 || player = JUGADOR 2
    (!player) ? addComponent<Callback>(enterButton, [&]() { hostButtonNameAction(); }) : addComponent<Callback>(enterButton, [&]() { clientButtonIPAction(); });

    addEntity(enterButton, _grp_UI);
}

void PlayStateMultiPlayer::createNameTextBox() {
    //CRA EL TEXTBLOCK
    nameTextBox = new Entity(_grp_UI);
    nameTextBox->setContext(this);
    addComponent<Transform>(nameTextBox, ONEPLAYER_BUTTON_POSITION, VECTOR_ZERO, BUTTON_WIDTH, BUTTON_HEIGHT, 0);
    UITextures_[nameTextBox] = new Texture(SDLUtils::instance()->renderer(), NAME_TEXT_BOX, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(COLOR_BLACK), build_sdlcolor(COLOR_WHITE));
    addEntity(nameTextBox, _grp_UI);
}

void PlayStateMultiPlayer::createWaitingTextBox() {
    //CREA EL TEXTO DE ESPERANDO
    waitingText = new Entity(_grp_UI);
    waitingText->setContext(this);
    addComponent<Transform>(waitingText, ONEPLAYER_BUTTON_POSITION, VECTOR_ZERO, BUTTON_WIDTH, BUTTON_HEIGHT, 0);
    UITextures_[waitingText] = new Texture(SDLUtils::instance()->renderer(), WAITING_TEXT, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(COLOR_BLACK), build_sdlcolor(COLOR_WHITE));
    addEntity(waitingText, _grp_UI);
   
}

void PlayStateMultiPlayer::createIpTextBox() {
    //CREA EL TEXTBOX DE IP
    ipTextBox = new Entity(_grp_UI);
    ipTextBox->setContext(this);
    addComponent<Transform>(ipTextBox, ONEPLAYER_BUTTON_POSITION, VECTOR_ZERO, BUTTON_WIDTH, BUTTON_HEIGHT, 0);
    UITextures_[ipTextBox] = new Texture(SDLUtils::instance()->renderer(), IP_TEXT, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(COLOR_BLACK), build_sdlcolor(COLOR_WHITE));
    addEntity(ipTextBox, _grp_UI);
}

void PlayStateMultiPlayer::selectButtonAction(bool player) {
    //CAMBIA LA UI
    deActivateSELECTHUD();
    createNameTextBox();
    createEnterButton(player);
}

void PlayStateMultiPlayer::hostButtonNameAction() {
    //CAMBIA LA UI
     name = gameCtrlSys_->getname();

    deActivateNAMEHUD();
    createWaitingTextBox();

    networkSys_->server();
}

void PlayStateMultiPlayer::clientButtonIPAction() {
    //CAMBIA LA UI Y EL CALBACK DEL BOTON ENTER
    name = gameCtrlSys_->getname();
    getComponent<Callback>(enterButton)->setCallback([&]() {
        deActivateIPHUD();
        networkSys_->client(gameCtrlSys_->getIp().c_str());
    });

    nameTextBox->setAlive(false);
    createIpTextBox();
}