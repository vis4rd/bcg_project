#pragma once

#include "ObjectAnimation.h"
#include <cmath>
/**
 * @brief      Class performing ring animations,the first image moves away in semicircle to the right
 * 			   and at the same time the second image appers in semicircle on the left side and covers the first one
 * 
 */
class RingAnimation : public ObjectAnimation
{
	public:
	/**
	 * Default constructor
	 */
	RingAnimation();
	/**
	 * @brief      Constructor setting animation startup parameters
	 *
	 * @param[in]  animation_length  The animation length
	 * @param[in]  animation_speed   The animation speed
	 * @param[in]  image1start       The image 1 start position
	 * @param[in]  image2start       The image 2 start position
	 * @param[in]  image1end         The image 1 end position 
	 * @param[in]  image2end         The image 2 end position
	 */
	explicit RingAnimation(
		const float &animation_length,
		const float &animation_speed,
		const em::Matrix4f &image1start,
		const em::Matrix4f &image2start,
		const em::Matrix4f &image1end,
		const em::Matrix4f &image2end);
	/**
	 * @brief      Default destructor
	 */
	~RingAnimation() = default;
	/**
	 * @brief      Performs transformations on the first image
	 *
	 * @param[in]  current_time  The current time animation
	 *
	 * @return     The image 1 frame.
	 */
	inline const em::Matrix4f getImage1Frame(const float &current_time) const override
	{	
		em::Matrix4f temp = m_image1Start;
		temp.translate(sf::Vector3f(
			1900.f * sin(M_PI * current_time/m_totalTime),
			0.f,
			1900.f * current_time/m_totalTime));
		return temp;
	}
	/**
	 * @brief      Performs transformations on the second image
	 *
	 * @param[in]  current_time  The current time of animation
	 *
	 * @return     The image 2 frame.
	 */
	inline const em::Matrix4f getImage2Frame(const float &current_time) const override
	{
		em::Matrix4f temp = m_image2Start;
		temp.translate(sf::Vector3f(
			1900.f * -sin(M_PI * current_time/m_totalTime),
			0.f,
			1900.f * (1.f - current_time/m_totalTime)));
		return temp;
	}

	protected:

};
