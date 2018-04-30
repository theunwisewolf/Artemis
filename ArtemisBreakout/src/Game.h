#pragma once

#include <string>
#include <vector>

#include <GL/glew.h>

#include "game/Level.h"
#include "utils/Math.h"

#include "graphics/AnimationSequence.h"

namespace ArtemisBreakout
{
class Game
{
private:
	static Game* instance;

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

	std::string m_GameDataPath;

	int levelIndex = -1;

public:
	Game(Window* window);

	static Game* i()
	{
		return instance;
	}

	void Update();
	void Render();
	
	std::vector<ArtemisBreakout::Level*> levels;

	void AddLevels(std::vector<ArtemisBreakout::Level*> levels) { this->levels = levels; }

	bool LoadLevel(Level* level);
	void UnloadLevel();

	inline void Pause() { m_Paused = true; };
	inline void Play()  { m_Paused = false; };

	inline std::string GameDataPath() const { return this->m_GameDataPath; }

	~Game();
};

}