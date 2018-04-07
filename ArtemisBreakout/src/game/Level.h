#pragma once

#include <string>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

#include <Parser.h>

#include <src/core/Shader.h>
#include <src/core/Window.h>
#include <src/core/Renderer2D.h>
#include <src/core/ShaderProgram.h>
#include <src/core/PolygonRenderer2D.h>

#include <src/game/GameObject.h>
#include <src/game/BallObject.h>
#include <src/game/BlockObject.h>
#include <src/game/PlatformObject.h>

#include <src/graphics/AnimationSequence.h>

#include <src/utils/Math.h>

#include <glm/gtc/matrix_transform.hpp>

#define LEVEL_PATH "/levels/"

namespace ArtemisBreakout
{
class Level
{
private:
	ShaderProgram m_ShaderProgram;
	ShaderProgram m_EllipseShaderProgram;

	Window* m_Window;

	// Level name
	std::string m_Level;
	std::string m_Data;

	struct Details
	{
		std::string m_LevelFriendlyName;
	} m_LevelDetails;

	// Artemis parser
	Artemis::Parser m_Parser;

	// Renderer
	Renderer2D m_Renderer;
	PolygonRenderer2D m_PolygonRenderer;

	std::vector<Tag*> m_Primitives;
	std::vector<GameObject*> m_GameObjects;
	std::vector<Tag*> m_PolygonalObjects;

	PlatformObject* m_Platform;
	BallObject* m_Ball;
	BallObject* m_BallB;

	const glm::vec3 BALL_VELOCITY;
	size_t m_BlocksDestroyed;

	AnimationSequence m_AnimationSequence;

	bool failed = false;

public:
	Level(const std::string& level, Window* window, const std::string& gameDataPath);
	~Level();

	// Loads this level
	bool Load();

	// Returns a Primitive
	GameObject* GetObject(std::string name);
	GameObject* GetObject(int id);

	// Updates Primitive
	//void UpdatePrimitive(Tag* primitive);

	inline PlatformObject* Platform() { return m_Platform; }
	inline BallObject* Ball() { return m_Ball; }
	inline BallObject* BallB() { return m_BallB; }

	// Renders the level
	void Render();

	// Checks for collisions between ball & objects
	void CheckCollisions(float deltaTime);

	AnimationSequence* Animations() { return &m_AnimationSequence; }
};
}