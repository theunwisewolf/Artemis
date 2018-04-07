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
#define WINDOW_TITLE	"Atari Breakout"

// Bootstrap
int main(int argc, char** argv)
{
	Window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	ArtemisBreakout::Level level("level2.aml", window);
	ArtemisBreakout::Game game(&window);

	game.LoadLevel(&level);

	const int LEFT		= -window.Width() / 2;
	const int RIGHT		=  window.Width() / 2;
	const int TOP		=  window.Height() / 2;
	const int BOTTOM	= -window.Height() / 2;

	//Rectangle* ball = (Rectangle*)level.GetPrimitive("ball");
	//Rectangle* platform = (Rectangle*)level.GetPrimitive("platform");

	while (window.ShouldClose() == false)
	{
		game.Render();

		game.Update();
		window.Update();
	}

	game.UnloadLevel();

	return 0;
}