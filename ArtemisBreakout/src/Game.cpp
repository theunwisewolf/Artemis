#include "Game.h"

namespace ArtemisBreakout
{

Game* Game::instance = nullptr;

Game::Game(Window* window) :
	m_Window(window),
	m_CurrentLevel(nullptr),
	m_LastTime(0.0f),
	LEFT(-window->Width() / 2),
	RIGHT(window->Width() / 2),
	TOP(window->Height() / 2),
	BOTTOM(-window->Height() / 2)
{
	instance = this;

	auto execPath = this->m_Window->ExecutablePath();

	auto pos = execPath.find_last_of('\\');
	execPath = execPath.substr(0, pos);
	pos = execPath.find_last_of('\\');

	this->m_GameDataPath = execPath.substr(0, pos) + "\\data";
}

void Game::Update()
{
	double currentTime = glfwGetTime();
	double deltaTime = currentTime - m_LastTime;

	m_CurrentLevel->Ball()->Move(deltaTime);
	m_CurrentLevel->CheckCollisions(deltaTime);

	if (!m_CurrentLevel->Animations()->IsPaused())
	{
		m_CurrentLevel->Animations()->Play(deltaTime);
	}

	if (m_Window->IsKeyDown(GLFW_KEY_LEFT) || m_Window->IsJoystickButtonPressed(JOYSTICK_BUTTON_LEFT) || m_Window->IsLeftStickMoved(JOYSTICK_LEFT_AXIS))
	{
		if ((m_CurrentLevel->Platform()->Position().x - m_CurrentLevel->Platform()->Width() / 2) > LEFT)
		{
			//m_CurrentLevel->Platform()->SetPosition(glm::vec3(m_CurrentLevel->Platform()->Position().x - 1, m_CurrentLevel->Platform()->Position().y, 0.0f));
			m_CurrentLevel->Platform()->MoveLeft(deltaTime);

			if (m_CurrentLevel->Ball()->OnPlatform())
			{
				m_CurrentLevel->Ball()->SetPosition(glm::vec3(m_CurrentLevel->Platform()->Position().x, m_CurrentLevel->Ball()->Position().y, 0.0f));
			}
		}
	}

	if (m_Window->IsKeyDown(GLFW_KEY_RIGHT) || m_Window->IsJoystickButtonPressed(JOYSTICK_BUTTON_RIGHT) || m_Window->IsLeftStickMoved(JOYSTICK_RIGHT_AXIS))
	{
		if ((m_CurrentLevel->Platform()->Position().x + m_CurrentLevel->Platform()->Width() / 2) < RIGHT)
		{
			//m_CurrentLevel->Platform()->SetPosition(glm::vec3(m_CurrentLevel->Platform()->Position().x + 1, m_CurrentLevel->Platform()->Position().y, 0.0f));
			m_CurrentLevel->Platform()->MoveRight(deltaTime);

			if (m_CurrentLevel->Ball()->OnPlatform())
			{
				m_CurrentLevel->Ball()->SetPosition(glm::vec3(m_CurrentLevel->Platform()->Position().x, m_CurrentLevel->Ball()->Position().y, 0.0f));
			}
		}
	}

	// Cycling through levels
	if (m_Window->IsKeyPressed(GLFW_KEY_1))
	{
		levelIndex--;

		if (levelIndex < 0)
		{
			levelIndex = this->levels.size() - 1;
		}

		this->UnloadLevel();
		this->LoadLevel(this->levels[levelIndex]);
	}
	if (m_Window->IsKeyPressed(GLFW_KEY_2))
	{
		levelIndex++;

		if (levelIndex >= this->levels.size())
		{
			levelIndex = 0;
		}
		
		this->UnloadLevel();
		this->LoadLevel(this->levels[levelIndex]);
	}

	// Quit Game
	if (m_Window->IsKeyPressed(GLFW_KEY_ESCAPE))
	{
		m_Window->ShouldClose(true);
	}

	if (m_Window->IsKeyDown(' ') || 
		m_Window->IsJoystickButtonPressed(JOYSTICK_BUTTON_A) ||
		m_Window->IsJoystickButtonPressed(JOYSTICK_BUTTON_B) ||
		m_Window->IsJoystickButtonPressed(JOYSTICK_BUTTON_X) ||
		m_Window->IsJoystickButtonPressed(JOYSTICK_BUTTON_Y)
	)
	{
		m_CurrentLevel->Ball()->OnPlatform(false);
	}

	m_LastTime = currentTime;
}

void Game::Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_CurrentLevel->Render();
}

bool Game::LoadLevel(Level* level)
{
	this->m_CurrentLevel = level;
	
	if (this->m_CurrentLevel->Load() == false)
	{
		std::cout << "ERROR: Game initialization failed." << std::endl;
		return false;
	}

	return true;
}

void Game::UnloadLevel()
{
	if (m_CurrentLevel == nullptr)
	{
		return;
	}

	// TODO: Fix this
	//delete m_CurrentLevel;

	m_CurrentLevel->Unload();
	m_CurrentLevel = nullptr;
}

Game::~Game()
{
	for (auto level : levels)
	{
		if (level)
		{
			delete level;
			level = nullptr;
		}
	}

	levels.clear();

	this->UnloadLevel();
}

}