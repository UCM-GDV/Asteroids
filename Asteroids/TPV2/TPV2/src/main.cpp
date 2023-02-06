// This file is part of the course TPV2@UCM - Samir Genaim

// Yi (Laura) Wang Qiu & Cristina Mora Velasco (Grupo 20)

#include <iostream>

#include "sdlutils/sdlutils_demo.h"
#include "sdlutils/Game.h"

int main(int ac, char **av) {
	try {
		Game();
	} catch (const std::string &e) { // catch exceptions thrown as strings
		std::cerr << e << std::endl;
	} catch (const char *e) { // catch exceptions thrown as char*
		std::cerr << e << std::endl;
	} catch (const std::exception &e) { // catch exceptions thrown as a sub-type of std::exception
		std::cerr << e.what();
	} catch (...) {
		std::cerr << "Caught and exception of unknown type ...";
	}

	return 0;
}

