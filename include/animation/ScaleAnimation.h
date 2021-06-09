#pragma once

#include "ObjectAnimation.h"

class ScaleAnimation : public ObjectAnimation
{
	public:

	ScaleAnimation();
	explicit ScaleAnimation(
		const float &animation_length,
		const float &animation_speed,
		const em::Matrix4f &image1start,
		const em::Matrix4f &image2start,
		const em::Matrix4f &image1end,
		const em::Matrix4f &image2end);

	~ScaleAnimation() = default;

	inline const em::Matrix4f getImage1Frame(const float &current_time) const override
	{	
		em::Matrix4f temp = m_image1Start;
		temp.translate(sf::Vector3<float>(0.f, 0.f, 1.f*(current_time/m_totalTime) ));
		return temp;
	}

	inline const em::Matrix4f getImage2Frame(const float &current_time) const override
	{
		em::Matrix4f temp = m_image2Start;
		temp.translate(sf::Vector3<float>
			(480.f-480.f*current_time/m_totalTime,
			340.f-340.f*current_time/m_totalTime,
			0.f));
		temp.scale(sf::Vector3<float>(1.f * current_time/m_totalTime, 1.f* current_time/m_totalTime, 1.f*current_time));
		return temp;
	}

	protected:

};