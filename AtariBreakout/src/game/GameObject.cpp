#include "GameObject.h"

namespace ArtemisBreakout
{

size_t GameObject::s_ObjectCount = 0;

GameObject::GameObject()
{
	s_ObjectCount++;
	m_ObjectId = s_ObjectCount;
}

GameObject::GameObject(const glm::vec3& position, const glm::vec2& size, const uint32_t& color, const std::string& name) :
	m_Position(position),
	m_Size(size),
	m_ObjectName(name)
{
	s_ObjectCount++;
	m_ObjectId = s_ObjectCount;
	::Color c(color);

	this->m_Color = Color::toThreeComponents(color);
}

void GameObject::SetSize(const glm::vec2& size)
{
	this->m_Size = size;
}

void GameObject::SetName(const std::string& name)
{
	this->m_ObjectName = name;
}

void GameObject::SetPosition(const glm::vec3& position)
{
	this->m_Position = position;
}

void GameObject::SetColor(const uint32_t& color)
{
	this->m_Color = Color::toThreeComponents(color);
}

bool GameObject::CollidesWith(GameObject* object)
{
	Rect boxA = this->BoundingBox();
	Rect boxB = object->BoundingBox();

	if (
		boxA.topLeft.x < boxB.topRight.x &&
		boxA.topRight.x > boxB.topLeft.x &&
		boxA.topLeft.y < boxB.topRight.y &&
		boxA.topRight.y > boxB.topLeft.y
	)
	{
		return true;
	}

	return false;
}

Rect GameObject::BoundingBox() const
{
	Rect box;

	box.topLeft = glm::vec2(this->m_Position.x - this->m_Size.x / 2, this->m_Position.y - this->m_Size.y / 2);
	box.topRight = glm::vec2(this->m_Position.x + this->m_Size.x / 2, this->m_Position.y - this->m_Size.y / 2);
	box.bottomLeft = glm::vec2(this->m_Position.x - this->m_Size.x / 2, this->m_Position.y + this->m_Size.y / 2);
	box.topRight = glm::vec2(this->m_Position.x + this->m_Size.x / 2, this->m_Position.y + this->m_Size.y / 2);

	return box;
}

}