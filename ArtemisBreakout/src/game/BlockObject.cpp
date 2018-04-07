#include "BlockObject.h"

namespace ArtemisBreakout
{

BlockObject::BlockObject() :
	e_PowerUp(PowerUps::NONE)
{

}

BlockObject::BlockObject(const glm::vec3& position, const glm::vec2& size, const uint32_t& color) :
	GameObject(position, size, color),
	e_PowerUp(PowerUps::NONE)
{

}

void BlockObject::Move(float deltatime)
{

}

void BlockObject::PowerUp(std::string powerup)
{
	if (powerup == "expand")
	{
		this->e_PowerUp = PowerUps::PLATFORM_EXPAND;
	}
	else if (powerup == "slowball")
	{
		this->e_PowerUp = PowerUps::BALL_SLOW;
	}
	else if (powerup == "fastball")
	{
		this->e_PowerUp = PowerUps::BALL_FAST;
	}
}

void BlockObject::Reset()
{

}

}