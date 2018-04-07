#include <string>
#include <random>
#include <chrono>
#include <fstream>
#include <iostream>

#include <GL/glew.h>

#include <src/Game.h>
#include <src/game/Level.h>
#include <src/core/Window.h>

// Window Settings
#define WINDOW_WIDTH	1280
#define WINDOW_HEIGHT	760
#define WINDOW_TITLE	"Artemis Breakout"

// Bootstrap
int main(int argc, char** argv)
{
	Window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	ArtemisBreakout::Game game(&window);
	ArtemisBreakout::Level level("level2.aml", &window, game.GameDataPath());

	if (game.LoadLevel(&level))
	{
		while (window.ShouldClose() == false)
		{
			game.Render();

			game.Update();
			window.Update();
		}
	}
	else
	{
		window.Close();
	}

	window.Close();
	game.UnloadLevel();

	std::cin.ignore();
	std::cin.get();

	return 0;
}