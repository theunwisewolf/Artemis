#include "AnimationSequence.h"

AnimationSequence::AnimationSequence() :
	m_Paused(false)
{

}

AnimationSequence::AnimationSequence(const std::vector<AnimationFrame*>& animationFrames) :
	m_Paused(false)
{
	// Copy animation frames to the current stack
	//std::copy(animationFrames.begin(), animationFrames.end(), m_AnimStack.begin());
}

void AnimationSequence::PushFrame(AnimationFrame* frame)
{
	m_AnimStack.push(frame);
}

void AnimationSequence::PopFrame()
{
	delete m_AnimStack.front();

	m_AnimStack.pop();
}

void AnimationSequence::Play(float deltaTime)
{
	if (!m_Paused && m_AnimStack.size())
	{
		// If the animation completes in this frame, pop it
		if (m_AnimStack.front()->Execute(deltaTime))
		{
			this->PopFrame();
		}
	}
}

void AnimationSequence::Pause()
{
	m_Paused = true;
}

void AnimationSequence::Unpause()
{
	m_Paused = false;
}

AnimationSequence::~AnimationSequence()
{

}