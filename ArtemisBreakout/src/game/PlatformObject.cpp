#include "PlatformObject.h"

namespace ArtemisBreakout
{

PlatformObject::PlatformObject()
{

}

PlatformObject::PlatformObject(const glm::vec3& position, const glm::vec2& size, const uint32_t& color, const glm::vec3& velocity) :
	GameObject( position, size, color, "platform" ),
	m_Velocity(velocity)
{

}

void PlatformObject::Move(float deltatime)
{

}

void PlatformObject::MoveLeft(float deltaTime)
{
	this->m_Position.x -= ((this->m_Velocity.x + this->m_Size.x) * deltaTime);
	//this->m_Position = glm::vec3(m_Position.x - 1, m_Position.y, 0.0f);
}

void PlatformObject::MoveRight(float deltaTime)
{
	this->m_Position.x += ((this->m_Velocity.x + this->m_Size.x) * deltaTime);
	//this->m_Position = glm::vec3(m_Position.x + 1, m_Position.y, 0.0f);
}

void PlatformObject::Reset()
{

}

}