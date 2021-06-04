#pragma once

#include "PixelAnimation.h"

class DimmingAnimation : public PixelAnimation
{
	public:

	DimmingAnimation();
	
	explicit DimmingAnimation(
		const float &animation_length,
		const float &animation_speed,
		std::vector<unsigned char> texture1_pixels, 
		std::vector<unsigned char> texture2_pixels);

	explicit DimmingAnimation(
		const float &animation_length,
		const float &animation_speed,
		const sf::Texture &texture1,
		const sf::Texture &texture2);

	~DimmingAnimation();


	inline const std::vector<unsigned char> getTexture1Frame(const float &current_time) const override
	{
		std::vector<unsigned char> temp = m_pixels1;

		if( current_time <= m_totalTime/2.f )
		{
			for(unsigned i=0; i<temp.size(); i+=4)
			{
				temp[i] -= static_cast<unsigned char>( static_cast<float>(temp[i]) * (current_time/(m_totalTime/2.f)) );
				temp[i+1] -= static_cast<unsigned char>( static_cast<float>(temp[i+1]) * (current_time/(m_totalTime/2.f)) );
				temp[i+2] -= static_cast<unsigned char>( static_cast<float>(temp[i+2]) * (current_time/(m_totalTime/2.f)) );
			}
		}
		else 
		{
			for(unsigned i=0; i<temp.size(); i+=4)
			{
				temp[i+3] = 0;  
			}
		}

		return temp;
	}


	inline const std::vector<unsigned char> getTexture2Frame(const float &current_time) const override
	{
		std::vector<unsigned char> temp = m_pixels2;

		if( current_time <= m_totalTime/2.f )
		{
			for(unsigned i=0; i<temp.size(); i+=4)
			{
				temp[i] = 0; 
				temp[i+1] = 0;
				temp[i+2] = 0;
			}
			
		}
		else 
		{
			for(unsigned i=0; i<temp.size(); i+=4)
			{
				temp[i] = static_cast<unsigned char> ( static_cast<float>(temp[i]) * ((current_time-m_totalTime/2.f) / (m_totalTime/2.f))  ) ;
				temp[i+1] = static_cast<unsigned char> ( static_cast<float>(temp[i+1]) * ((current_time-m_totalTime/2.f) / (m_totalTime/2.f)) );
				temp[i+2] = static_cast<unsigned char> ( static_cast<float>(temp[i+2]) * ((current_time-m_totalTime/2.f) / (m_totalTime/2.f)) );
				temp[i+3] = static_cast<unsigned char>( static_cast<float>(temp[i+3]) * ((current_time-m_totalTime/2.f) / (m_totalTime/2.f)) );  
			}
		}
		return temp;

	} 
 



	protected:



};