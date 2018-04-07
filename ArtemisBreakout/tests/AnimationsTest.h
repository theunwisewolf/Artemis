#pragma once

#include <src/game/Level.h>
#include <src/utils/Math.h>
#include <src/graphics/AnimationSequence.h>
#include <glm/common.hpp>

#if 0
static void AnimationTest()
{
	AnimationFrame *radiusAnimation = new AnimationFrame([this](float deltaTime) {
		float radius = m_CurrentLevel->Ball()->Radius();

		radius = lerp(radius, 100, deltaTime * 2);

		m_CurrentLevel->Ball()->Radius(radius);
		m_CurrentLevel->BallB()->Radius(radius);

		return false;
	});

	AnimationFrame *positionAnimation = new AnimationFrame([this](float deltaTime) {
		float x = m_CurrentLevel->Ball()->Position().x;

		// Completed
		if (x >= 198) {
			return true;
		}

		x = lerp(x, 200, deltaTime * 2);
		m_CurrentLevel->Ball()->SetPosition(glm::vec3(x, m_CurrentLevel->Ball()->Position().y, 0.0f));
		m_CurrentLevel->BallB()->SetPosition(glm::vec3(-x, m_CurrentLevel->BallB()->Position().y, 0.0f));

		return false;
	});

	AnimationFrame *radiusAnimationSmall = new AnimationFrame([this](float deltaTime) {
		float radius = m_CurrentLevel->Ball()->Radius();

		// Completed
		if (radius <= 41) {
			return true;
		}

		radius = lerp(radius, 40, deltaTime * 2);
		m_CurrentLevel->Ball()->Radius(radius);
		m_CurrentLevel->BallB()->Radius(radius);

		return false;
	});

	AnimationFrame *circularRotation = new AnimationFrame([this](float deltaTime) {
		static float radius = 100.0f;

		static float theta = acosf(m_CurrentLevel->Ball()->Position().x / radius);
		theta += deltaTime * 4;
		//float angle = m_CurrentLevel->Ball()->Angle();

		//theta = lerp(theta, 2 * 3.14, deltaTime);

		if (theta >= (2 * 3.14f))
		{
			theta = 0.0f;
		}

		float x = radius * cosf(theta);
		float y = radius * sin(theta);

		m_CurrentLevel->Ball()->SetPosition(glm::vec3(x, y, 0.0f));
		m_CurrentLevel->BallB()->SetPosition(glm::vec3(-x, -y, 0.0f));


		//radius = lerp(radius, 40, deltaTime * 2);
		//m_CurrentLevel->Ball()->Radius(radius);
		//m_CurrentLevel->BallB()->Radius(radius);

		return false;
	});

	AnimationSequence* seq = new AnimationSequence();
	AnimationSequence* seq2 = new AnimationSequence();

	//seq->PushFrame(radiusAnimation);
	//seq->PushFrame(positionAnimation);
	//seq->PushFrame(radiusAnimationSmall);
	seq->PushFrame(circularRotation);
	seq2->PushFrame(radiusAnimation);
}

#endif