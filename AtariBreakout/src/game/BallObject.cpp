#include "BallObject.h"

#include <GLFW\glfw3.h>

namespace ArtemisBreakout
{

BallObject::BallObject(
	const glm::vec3& position, 
	const uint32_t& color,
	const glm::vec2& windowBounds, 
	const float& radius,
	const glm::vec3& velocity
) :
	GameObject( position, glm::vec2(radius * 2, radius * 2), color, "ball" ),
	m_OnPlatform(true),
	m_Radius(radius),
	m_WindowBounds(windowBounds),
	m_Velocity(velocity),
	LEFT(-this->m_WindowBounds.x / 2),
	RIGHT(this->m_WindowBounds.x / 2),
	TOP(this->m_WindowBounds.y / 2),
	BOTTOM(-this->m_WindowBounds.y / 2)
{
}

glm::vec3 BallObject::Move(float deltatime)
{
	if (!this->m_OnPlatform)
	{
		this->m_Position += ((this->m_Velocity + this->m_Size.x) * deltatime);

		if ((this->m_Position.x - this->m_Size.x / 2.0f) <= LEFT)
		{
			this->m_Velocity.x = -this->m_Velocity.x;
			this->m_Position.x = LEFT + this->m_Size.x / 2.0f;
		}
		else if ((this->m_Position.x + this->m_Size.x / 2.0f) >= RIGHT)
		{
			this->m_Velocity.x = -this->m_Velocity.x;
			this->m_Position.x = RIGHT - this->m_Size.x / 2.0f;
		}
		else if ((this->m_Position.y + this->m_Size.y / 2.0f) >= TOP)
		{
			this->m_Velocity.y = -this->m_Velocity.y;
			this->m_Position.y = TOP - this->m_Size.y / 2.0f;
		}
		
		/*static long l = glfwGetTime();
		long nt = l;
		if (l % 20 == 0)
		{
			this->m_Velocity.y = 0.5* m_Velocity.y;
		}
		if (l == nt + 5)
		{
			this->m_Velocity.y = 2* m_Velocity.y;
		}*/
	}
	

	return this->m_Position;
}

bool BallObject::CollidesWith(GameObject* object)
{
	glm::vec2 halfExtents = glm::vec2(object->Size().x / 2.0f, object->Size().y / 2.0f);
	glm::vec2 difference = glm::vec2(m_Position.x, m_Position.y) - glm::vec2(object->Position().x, object->Position().y);
	glm::vec2 clamped = glm::clamp(difference, -halfExtents, halfExtents);

	glm::vec2 closest = glm::vec2(object->Position().x, object->Position().y) + clamped;
	difference = closest - glm::vec2(m_Position.x, m_Position.y);

	return glm::length(difference) < m_Radius;
	return GameObject::CollidesWith(object);
}

void BallObject::Reset()
{

}

}
