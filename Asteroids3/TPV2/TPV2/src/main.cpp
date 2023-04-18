// Yi (Laura) Wang Qiu & Cristina Mora Velasco (Grupo 20)

#include <iostream>
#include "game/Game.h"
#include "utils/checkML.h"

int main(int ac, char **av) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game* game = nullptr;
	try {
		game = new Game();
		game->run();
	} catch (const std::string &e) {
		std::cerr << e << std::endl;
	} catch (const char *e) {
		std::cerr << e << std::endl;
	} catch (const std::exception &e) {
		std::cerr << e.what();
	} catch (...) {
		std::cerr << "Caught and exception of unknown type ...";
	}
	delete game;

	return 0;
}

