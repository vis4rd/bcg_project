#pragma once

#include "ObjectAnimation.h"

class DebugAnimation : public ObjectAnimation
{
public:
	DebugAnimation() : ObjectAnimation() { }
	explicit DebugAnimation(
		const float &animation_length,
		const float &animation_speed,
		const em::Matrix4f &image1start,
		const em::Matrix4f &image2start,
		const em::Matrix4f &image1end,
		const em::Matrix4f &image2end)
	: ObjectAnimation(
		animation_length,
		animation_speed,
		image1start,
		image2start,
		image1end,
		image2end)
	{ }

	~DebugAnimation() = default;

	/////////////////////////
	// Image position: 474, 297.5, 0
	/////////////////////////
	

	inline const em::Matrix4f getImage1Frame(const float &current_time) const override
	{	
		em::Matrix4f temp = m_image1Start;
		temp.translate(sf::Vector3f(0.f, -297.5f, 0.f));
		temp.rotateX(180.f * current_time / m_totalTime);
		temp.translate(sf::Vector3f(0.f, 297.5f, 0.f));
		return temp;
	}

	inline const em::Matrix4f getImage2Frame(const float &current_time) const override
	{
		em::Matrix4f temp = m_image2Start;

		return temp;
	}
};
