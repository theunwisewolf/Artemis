#pragma once

#include <glm/common.hpp>
#include <src/game/GameObject.h>

namespace ArtemisBreakout
{

class PlatformObject : public GameObject
{
private:
	glm::vec3 m_Velocity;

public:
	PlatformObject();
	PlatformObject(const glm::vec3& position, const glm::vec2& size, const uint32_t& color, const glm::vec3& velocity);

	void Move(float deltatime);
	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);

	void Reset();
};

}