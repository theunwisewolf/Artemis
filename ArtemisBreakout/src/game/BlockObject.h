#pragma once

#include <glm/common.hpp>
#include <src/game/GameObject.h>

namespace ArtemisBreakout
{

enum class PowerUps {
	PLATFORM_EXPAND,
	BALL_FAST,
	BALL_SLOW,
	NONE
};

class BlockObject : public GameObject
{
private:
	PowerUps e_PowerUp;

public:
	BlockObject();
	BlockObject(const glm::vec3& position, const glm::vec2& size, const uint32_t& color);

	void PowerUp(std::string powerup);
	PowerUps PowerUp() const { return e_PowerUp; }

	void Move(float deltatime);
	void Reset();
};

}