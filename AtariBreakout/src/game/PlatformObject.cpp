#include "PlatformObject.h"

namespace ArtemisBreakout
{

PlatformObject::PlatformObject()
{

}

PlatformObject::PlatformObject(const glm::vec3& position, const glm::vec2& size, const uint32_t& color) :
	GameObject( position, size, color, "platform" )
{

}

void PlatformObject::Move(float deltatime)
{

}

void PlatformObject::Reset()
{

}

}