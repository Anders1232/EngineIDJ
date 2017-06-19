#include <iostream>

#include "Game.h"
#include "TitleState.h"

using std::cout;
using std::endl;

int main(int argc, char **argv) {
	Game game(std::string("Towers of Madness"), 1024, 600);
	game.Push(new TitleState());
	game.Run();
	return 0;
}

