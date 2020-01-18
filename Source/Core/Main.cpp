#include "Game.h"
#include "Util.h"

int main(int argc, char** argv)
{
	Freeking::Game game(argc, argv);
	game.Run();

	return EXIT_SUCCESS;
}