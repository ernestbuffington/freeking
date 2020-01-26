#include "Game.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int argc, char** argv)
{
	Freeking::Game game(argc, argv);
	game.Run();

	return EXIT_SUCCESS;
}