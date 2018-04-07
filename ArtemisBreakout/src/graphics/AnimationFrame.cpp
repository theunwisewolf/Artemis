#include "AnimationFrame.h"

AnimationFrame::AnimationFrame(const std::function<bool(float)>& action) :
	m_Completed(false),
	m_Action(action)
{

}

AnimationFrame::~AnimationFrame()
{

}

bool AnimationFrame::Execute(float deltaTime)
{
	return m_Action(deltaTime);
}