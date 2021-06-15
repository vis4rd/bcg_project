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
	 * 
	 * 
	 * searching darkest and brightness pixel, (avrage of (r,g,b)) and after that:
	 *  key = (1 - progres) * (brightness - darkest + 1) + darkest
	 *  if pixel brightness > key then we hidding that one. 
	 * 
	 */
	inline const std::vector<unsigned char> getTexture1Frame(const float &current_time) const override
	{
		std::vector<unsigned char> out = m_pixels1;
		std::vector<unsigned char> temp = m_pixels2;
		unsigned char brightness = 0 , darkest = 255;
		float key = (m_totalTime-current_time)/m_totalTime;

		//making sure that vectors are equal in size
		unsigned bigger = out.size() > temp.size() ? out.size() : temp.size();
		if(bigger != temp.size())
		{
			temp.resize(bigger);
		}
		if(bigger != out.size())
		{
			out.resize(bigger);
		}

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
	 * 
	 * 
	 * No changes - same image whole aniamtion time
	 */
	inline const std::vector<unsigned char> getTexture2Frame(const float &current_time) const override
	{
		return m_pixels2;
	} 
 
};
