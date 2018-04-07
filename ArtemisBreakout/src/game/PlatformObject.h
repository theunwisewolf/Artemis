#pragma once

#include <glm/common.hpp>
#include <src/game/GameObject.h>

namespace ArtemisBreakout
{

class PlatformObject : public GameObject
{
public:
	PlatformObject();
	PlatformObject(const glm::vec3& position, const glm::vec2& size, const uint32_t& color);

	void Move(float deltatime);
	void Reset();
};

}