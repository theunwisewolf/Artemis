#pragma once

#include <functional>

class AnimationFrame
{
private:
	bool m_Completed;
	std::function<bool(float)> m_Action;

public:
	bool Completed() const { return m_Completed; }

	AnimationFrame(const std::function<bool(float)>& action);
	~AnimationFrame();

	bool Execute(float deltaTime);
};