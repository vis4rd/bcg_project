#pragma once

#include "PixelAnimation.h"


/**
 * @brief      This class performs animation with alpha oppasity manipulation,
 * 				brightness pixels of the secend images appers sooner,
 * 				darkests ones after them 
 */	
class ByBrightnessAnimation : public PixelAnimation
{
	public:

	/**
	 * Default constructor
	 */
	ByBrightnessAnimation();
	

	/**
	 * @brief      The constructor with settings of animation
	 *
	 * @param      animation_length  The animation length
	 * @param      animation_speed   The animation speed
	 * @param      texture1_pixels   The texture of start image
	 * @param      texture2_pixels   The texture of end image
	 */
	explicit ByBrightnessAnimation(
		const float &animation_length,
		const float &animation_speed,
		std::vector<unsigned char> texture1_pixels, 
		std::vector<unsigned char> texture2_pixels);

	/**
	 * @brief      The constructor with settings of animation
	 *
	 * @param      animation_length  The animation length
	 * @param      animation_speed   The animation speed
	 * @param      texture1_pixels   The texture of start image
	 * @param      texture2_pixels   The texture of end image
	 */
	explicit ByBrightnessAnimation(
		const float &animation_length,
		const float &animation_speed,
		const sf::Texture &texture1,
		const sf::Texture &texture2);

	/**
	 * @brief      Dectructor
	 */
	~ByBrightnessAnimation();


	/**
	 * @brief      Returns how texture of start image should look.
	 *
	 * @param      current_time  The current time
	 *
	 * @return     The first image look in specific time.
	 */
	inline const std::vector<unsigned char> getTexture1Frame(const float &current_time) const override
	{
		std::vector<unsigned char> temp = m_pixels2;
		std::vector<unsigned char> out = m_pixels1;
		unsigned char brightness = 0 , darkest = 255;
		float key = (m_totalTime-current_time)/m_totalTime;

		// searching brightest pixel
		for(unsigned i=0; i<temp.size(); i+=4)
		{
			if( (temp[i] + temp[i+1] + temp[i+2])/3 > brightness )
			{
				brightness = (temp[i] + temp[i+1] + temp[i+2])/3;
			}
			
		}

		// searching darkest pixel
		for(unsigned i=0; i<temp.size(); i+=4)
		{
			if( (temp[i] + temp[i+1] + temp[i+2])/3 < darkest )
			{
				darkest = (temp[i] + temp[i+1] + temp[i+2])/3;
			}
		
		}

		key = ( key * (brightness - darkest + 1) + darkest ) ;

		for(unsigned i=0; i<temp.size(); i+=4)
		{
			if(	 (temp[i] + temp[i+1] + temp[i+2])/3 >= static_cast<unsigned char>(key))
			{
				out[i+3] = 0;
			}   	

		}
	
		return out;
	}


	/**
	 * @brief      Returns how texture of ending image should look.
	 *
	 * @param      current_time  The current time
	 *
	 * @return     The first image look in specific time.
	 */
	inline const std::vector<unsigned char> getTexture2Frame(const float &current_time) const override
	{
		return m_pixels2;
	} 
 
};