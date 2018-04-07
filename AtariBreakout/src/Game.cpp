#include "Game.h"

namespace ArtemisBreakout
{

Game::Game(Window* window) :
	m_Window(window),
	m_CurrentLevel(nullptr),
	m_LastTime(0.0f),
	LEFT(-window->Width() / 2),
	RIGHT(window->Width() / 2),
	TOP(window->Height() / 2),
	BOTTOM(-window->Height() / 2)
{
	AnimationFrame *radiusAnimation = new AnimationFrame([this](float deltaTime) {
		float radius = m_CurrentLevel->Ball()->Radius();

		radius = lerp(radius, 100, deltaTime * 2);
		
		m_CurrentLevel->Ball()->Radius(radius);
		m_CurrentLevel->BallB()->Radius(radius);

		return false;
	});

	AnimationFrame *positionAnimation = new AnimationFrame([this](float deltaTime) {
		float x = m_CurrentLevel->Ball()->Position().x;

		// Completed
		if (x >= 198) {
			return true;
		}

		x = lerp(x, 200, deltaTime * 2);
		m_CurrentLevel->Ball()->SetPosition(glm::vec3(x, m_CurrentLevel->Ball()->Position().y, 0.0f));
		m_CurrentLevel->BallB()->SetPosition(glm::vec3(-x, m_CurrentLevel->BallB()->Position().y, 0.0f));

		return false;
	});

	AnimationFrame *radiusAnimationSmall = new AnimationFrame([this](float deltaTime) {
		float radius = m_CurrentLevel->Ball()->Radius();

		// Completed
		if (radius <= 41) {
			return true;
		}

		radius = lerp(radius, 40, deltaTime * 2); 
		m_CurrentLevel->Ball()->Radius(radius);
		m_CurrentLevel->BallB()->Radius(radius);

		return false;
	});

	AnimationFrame *circularRotation = new AnimationFrame([this](float deltaTime) {
		static float radius = 100.0f;

		static float theta = acosf( m_CurrentLevel->Ball()->Position().x / radius );
		theta += deltaTime * 4;
		//float angle = m_CurrentLevel->Ball()->Angle();

		//theta = lerp(theta, 2 * 3.14, deltaTime);

		if (theta >= (2 * 3.14f))
		{
			theta = 0.0f;
		}

		float x = radius * cosf(theta);
		float y = radius * sin(theta);

		m_CurrentLevel->Ball()->SetPosition(glm::vec3(x, y, 0.0f));
		m_CurrentLevel->BallB()->SetPosition(glm::vec3(-x, -y, 0.0f));


		//radius = lerp(radius, 40, deltaTime * 2);
		//m_CurrentLevel->Ball()->Radius(radius);
		//m_CurrentLevel->BallB()->Radius(radius);

		return false;
	});

	//_seq.PushFrame(radiusAnimation);
	//_seq.PushFrame(positionAnimation);
	//_seq.PushFrame(radiusAnimationSmall);
	_seq.PushFrame(circularRotation);
	_seq2.PushFrame(radiusAnimation);
}

void Game::Update()
{
	double currentTime = glfwGetTime();
	double deltaTime = currentTime - m_LastTime;

	m_CurrentLevel->Ball()->Move(deltaTime);
	m_CurrentLevel->CheckCollisions(deltaTime);

	//_seq.Play(deltaTime);
	//_seq2.Play(deltaTime);

	if (!m_CurrentLevel->Animations()->IsPaused())
	{
		m_CurrentLevel->Animations()->Play(deltaTime);
	}

	if (m_Window->IsKeyDown(GLFW_KEY_LEFT) || m_Window->IsJoystickButtonPressed(JOYSTICK_BUTTON_LEFT) || m_Window->IsLeftStickMoved(JOYSTICK_LEFT_AXIS))
	{
		if ((m_CurrentLevel->Platform()->Position().x - m_CurrentLevel->Platform()->Width() / 2) > LEFT)
		{
			m_CurrentLevel->Platform()->SetPosition(glm::vec3(m_CurrentLevel->Platform()->Position().x - 1, m_CurrentLevel->Platform()->Position().y, 0.0f));
			
			if(m_CurrentLevel->Ball()->OnPlatform())
				m_CurrentLevel->Ball()->SetPosition(glm::vec3(m_CurrentLevel->Ball()->Position().x - 1, m_CurrentLevel->Ball()->Position().y, 0.0f));
		}
	}

	if (m_Window->IsKeyDown(GLFW_KEY_RIGHT) || m_Window->IsJoystickButtonPressed(JOYSTICK_BUTTON_RIGHT) || m_Window->IsLeftStickMoved(JOYSTICK_RIGHT_AXIS))
	{
		if ((m_CurrentLevel->Platform()->Position().x + m_CurrentLevel->Platform()->Width() / 2) < RIGHT)
		{
			m_CurrentLevel->Platform()->SetPosition(glm::vec3(m_CurrentLevel->Platform()->Position().x + 1, m_CurrentLevel->Platform()->Position().y, 0.0f));
			
			if (m_CurrentLevel->Ball()->OnPlatform())
				m_CurrentLevel->Ball()->SetPosition(glm::vec3(m_CurrentLevel->Ball()->Position().x + 1, m_CurrentLevel->Ball()->Position().y, 0.0f));
		}
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

void Game::LoadLevel(Level* level)
{
	this->m_CurrentLevel = level;
	this->m_CurrentLevel->Load();
}

void Game::UnloadLevel()
{
	if (m_CurrentLevel == nullptr)
	{
		return;
	}

	// TODO: Fix this
	//delete m_CurrentLevel;
	m_CurrentLevel = nullptr;
}

Game::~Game()
{
	this->UnloadLevel();
}

}