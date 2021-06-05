#pragma once

#include "PixelAnimation.h"

class ByBrightnessAnimation : public PixelAnimation
{
	public:

	ByBrightnessAnimation();
	
	explicit ByBrightnessAnimation(
		const float &animation_length,
		const float &animation_speed,
		std::vector<unsigned char> texture1_pixels, 
		std::vector<unsigned char> texture2_pixels);

	explicit ByBrightnessAnimation(
		const float &animation_length,
		const float &animation_speed,
		const sf::Texture &texture1,
		const sf::Texture &texture2);

	~ByBrightnessAnimation();


	inline const std::vector<unsigned char> getTexture1Frame(const float &current_time) const override
	{
		std::vector<unsigned char> temp = m_pixels2;
		std::vector<unsigned char> out = m_pixels1;
		unsigned char brightnes = 0 , darknest = 255;
		float key = (m_totalTime-current_time)/m_totalTime;

		// searching brightest pixel
		for(unsigned i=0; i<temp.size(); i+=4)
		{
			if( (temp[i] + temp[i+1] + temp[i+2])/3 > brightnes )
			{
				brightnes = (temp[i] + temp[i+1] + temp[i+2])/3;
			}
		}

		// searching darkest pixel
		for(unsigned i=0; i<temp.size(); i+=4)
		{
			if( (temp[i] + temp[i+1] + temp[i+2])/3 < darknest )
			{
				darknest = (temp[i] + temp[i+1] + temp[i+2])/3;
			}
		}

		key = key * (brightnes - darknest);
		std::cout << key << std::endl;
		std::cout << static_cast<unsigned char>(key) << std::endl;


		for(unsigned i=0; i<temp.size(); i+=4)
		{
			if(	 (temp[i] + temp[i+1] + temp[i+2])/3 > static_cast<unsigned char>(key) )
			{
				out[i+3] = 0;
			}   		
		}
	
		return out;
	}


	inline const std::vector<unsigned char> getTexture2Frame(const float &current_time) const override
	{
		return m_pixels2;
	} 
 
};