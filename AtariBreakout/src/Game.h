#pragma once

#include <GL/glew.h>

#include "game/Level.h"
#include "utils/Math.h"

#include "graphics/AnimationSequence.h"

namespace ArtemisBreakout
{

class Game
{
private:
	float m_DeltaTime;

	size_t m_Width;
	size_t m_Height;

	bool m_Paused;

	Level* m_CurrentLevel;
	Window* m_Window;

	float m_LastTime;

	const int LEFT;
	const int RIGHT;
	const int TOP;
	const int BOTTOM;

	AnimationSequence _seq;
	AnimationSequence _seq2;

public:
	Game(Window* window);

	void Update();
	void Render();

	void LoadLevel(Level* level);
	void UnloadLevel();

	inline void Pause() { m_Paused = true; };
	inline void Play()  { m_Paused = false; };

	~Game();
};

}