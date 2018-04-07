#pragma once

#include <vector>
#include <algorithm>
#include <queue>

#include "AnimationFrame.h"

class AnimationSequence
{
private:
	std::queue<AnimationFrame*> m_AnimStack;
	bool m_Paused;

public:
	AnimationSequence();
	AnimationSequence(const std::vector<AnimationFrame*>& animationFrames);

	~AnimationSequence();

	void PushFrame(AnimationFrame* frame);
	void PopFrame();

	void Play(float deltaTime);
	void Pause();
	void Unpause();

	bool IsPaused() const { return m_Paused; }
};