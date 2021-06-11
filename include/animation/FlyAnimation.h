#pragma once

#include "ObjectAnimation.h"

class FlyAnimation : public ObjectAnimation
{
	public:

	FlyAnimation();
	explicit FlyAnimation(
		const float &animation_length,
		const float &animation_speed,
		const em::Matrix4f &image1start,
		const em::Matrix4f &image2start,
		const em::Matrix4f &image1end,
		const em::Matrix4f &image2end);

	~FlyAnimation() = default;

	inline const em::Matrix4f getImage1Frame(const float &current_time) const override
	{	
		em::Matrix4f temp = m_image1Start;
		
		if(current_time<=(m_totalTime/2))
		{
			temp.translate(sf::Vector3<float>(480.f*current_time/(m_totalTime/2.0f), 340.f*current_time/(m_totalTime/2.0f), -1.f * (current_time/m_totalTime)));
			temp.scale(sf::Vector3f(1.f *(1 - current_time/(m_totalTime/2.0f)), 1.f*(1 - current_time/(m_totalTime/2.0f)), 1.f));
		}
		else
		{
			temp.scale(sf::Vector3<float>(0.f, 0.f, 0.f));
		}
		
		return temp;
	}

	inline const em::Matrix4f getImage2Frame(const float &current_time) const override
	{
		em::Matrix4f temp = m_image2Start;

		if(current_time>m_totalTime/2)
		{
		temp.translate(sf::Vector3<float>(480.f-(480.f*2.f*(current_time-(m_totalTime/2))/(m_totalTime)), 340.f-(340.f*2.f*(current_time-(m_totalTime/2))/(m_totalTime)), -1.f * (current_time/m_totalTime)));
		temp.scale(sf::Vector3<float>(1.f *2.f*(current_time-(m_totalTime/2))/(m_totalTime/1.f), 1.f*2.f*(current_time-(m_totalTime/2))/(m_totalTime/1.f), 1.f*current_time));
		}

		else
		{
			temp.translate(sf::Vector3<float>(500.f, 500.f, 1.f));
			temp.scale(sf::Vector3<float>(0.f, 0.f,0.f));
		}
		
		return temp;
	}

	protected:

};