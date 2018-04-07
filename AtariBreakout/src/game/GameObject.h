#pragma once

#include <string>

#include <src/core/Color.h>

#include <glm/common.hpp>

struct Rect
{
	glm::vec2 topLeft;
	glm::vec2 topRight;
	glm::vec2 bottomLeft;
	glm::vec2 bottomRight;
};

namespace ArtemisBreakout
{

class GameObject
{
public:
	static size_t s_ObjectCount;

protected:
	std::string m_ObjectName;
	size_t m_ObjectId;

	glm::vec3 m_Position;
	glm::vec2 m_Size;
	glm::vec4 m_Color;
	
public:
	GameObject();
	GameObject(const glm::vec3& position, const glm::vec2& size, const uint32_t& color, const std::string& name = "");

	void SetSize(const glm::vec2& size);
	void SetPosition(const glm::vec3& position);
	void SetName(const std::string& name);
	void SetColor(const uint32_t& color);

	virtual bool CollidesWith(GameObject* object);
	
	Rect BoundingBox() const;

	inline int ID() const { return this->m_ObjectId; }
	
	inline std::string Name() const { return this->m_ObjectName; }
	inline glm::vec3 Position() const { return this->m_Position; }
	inline glm::vec2 Size() const { return this->m_Size; }
	
	inline void Size(const glm::vec2& size) { this->m_Size = size; }

	inline float Width() const { return this->m_Size.x; }
	inline float Height() const { return this->m_Size.y; }

	inline glm::vec4 Color() const { return this->m_Color; }
	
	virtual void Update() {}
};

}