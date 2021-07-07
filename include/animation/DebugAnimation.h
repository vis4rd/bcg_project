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
	// Canvas size: 948, 595
	/////////////////////////
	

	inline const em::Matrix4f getImage1Frame(const float &current_time) const override
	{	
		em::Matrix4f temp = m_image1Start;
		temp.rotateZ(180.f * current_time / m_totalTime);
		return temp;
	}

	inline const em::Matrix4f getImage2Frame(const float &current_time) const override
	{
		em::Matrix4f temp = m_image2Start;

		return temp;
	}
};
