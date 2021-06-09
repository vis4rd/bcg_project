#pragma once

#include "ObjectAnimation.h"
#include <cmath>

class RingAnimation : public ObjectAnimation
{
	public:

	RingAnimation();
	explicit RingAnimation(
		const float &animation_length,
		const float &animation_speed,
		const em::Matrix4f &image1start,
		const em::Matrix4f &image2start,
		const em::Matrix4f &image1end,
		const em::Matrix4f &image2end);

	~RingAnimation() = default;

	inline const em::Matrix4f getImage1Frame(const float &current_time) const override
	{	
		em::Matrix4f temp = m_image1Start;
		temp.translate(sf::Vector3f(
			1150.f*cos(current_time/m_totalTime)*(1.14*current_time/m_totalTime),
			340.f*cos(current_time/m_totalTime)*(current_time/m_totalTime),
			((current_time < m_totalTime/2) ? -1.f : 1.f * (current_time/m_totalTime))));
		temp.scale(sf::Vector3f(1.f *(1 - current_time/m_totalTime), 1.f*(1 - current_time/m_totalTime), 1.f));
		return temp;
	}

	inline const em::Matrix4f getImage2Frame(const float &current_time) const override
	{
		em::Matrix4f temp = m_image2Start;
		temp.translate(sf::Vector3<float>(480.f-1150.f*current_time/m_totalTime*cos(1.14*current_time/m_totalTime), 340.f-630.f*current_time/m_totalTime*cos(current_time/m_totalTime), 0.f));
		temp.scale(sf::Vector3<float>(1.f * current_time/m_totalTime, 1.f* current_time/m_totalTime, 0.5f));
		return temp;
	}

	protected:

};
