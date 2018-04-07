#pragma once

#include <glm/common.hpp>
#include <src/game/GameObject.h>

namespace ArtemisBreakout
{

class BallObject : public GameObject
{
private:
	float m_Radius;
	bool m_OnPlatform;

	glm::vec3 m_Velocity;
	glm::vec2 m_WindowBounds;

	const int LEFT;
	const int RIGHT;
	const int TOP;
	const int BOTTOM;

public:
	BallObject(const glm::vec3& position, const uint32_t& color, const glm::vec2& windowBounds, const float& radius, const glm::vec3& velocity);

	glm::vec3 Move(float deltatime);
	void Reset();

	void OnPlatform(bool val) { m_OnPlatform = val; }
	bool OnPlatform() { return m_OnPlatform; }

	void Velocity(const glm::vec3& velocity) { this->m_Velocity = velocity; };
	glm::vec3 Velocity() { return m_Velocity; }

	inline void Radius(const float& radius) { this->m_Radius = radius; }
	inline float Radius() const { return this->m_Radius; }

	bool CollidesWith(GameObject* object) override;
};

}