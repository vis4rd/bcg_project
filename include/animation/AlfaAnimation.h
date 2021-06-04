#pragma once

#include "PixelAnimation.h"

class AlfaAnimation : public PixelAnimation
{
	public:

	AlfaAnimation();
	
	explicit AlfaAnimation(
		const float &animation_length,
		const float &animation_speed,
		std::vector<unsigned char> texture1_pixels, 
		std::vector<unsigned char> texture2_pixels);

	explicit AlfaAnimation(
		const float &animation_length,
		const float &animation_speed,
		const sf::Texture &texture1,
		const sf::Texture &texture2);

	~AlfaAnimation();


	inline const std::vector<unsigned char> getTexture1Frame(const float &current_time) const override
	{
		std::vector<unsigned char> temp = m_pixels1;
		for(unsigned i=3; i<temp.size(); i+=4)
		{
			temp[i] = static_cast<unsigned char>( static_cast<float>(temp[i]) - (static_cast<float>(temp[i]) * (current_time/m_totalTime)) );
		}
			
		return temp;
	}


	inline const std::vector<unsigned char> getTexture2Frame(const float &current_time) const override
	{
		std::vector<unsigned char> temp = m_pixels2;
		for(unsigned i=3; i<temp.size(); i+=4)
		{
			temp[i] = static_cast<unsigned char>( (static_cast<float>(temp[i]) * (current_time/m_totalTime)) ) ;
		}
			
		return temp;
	} 
 
	protected:
};