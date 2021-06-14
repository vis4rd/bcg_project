#pragma once

#include "PixelAnimation.h"


/**
 * @brief 	This class performs animation of dimming first image to black,
 * 			After that new image appears from black and getting brighter
 * 			
 */
class DimmingAnimation : public PixelAnimation
{
	public:

	/**
	 * Default constructor
	 */
	DimmingAnimation();
	
	/**
	 * @brief      The constructor with settings of animation
	 *
	 * @param      animation_length  The animation length
	 * @param      animation_speed   The animation speed
	 * @param      texture1_pixels   The texture of start image
	 * @param      texture2_pixels   The texture of end image
	 */
	explicit DimmingAnimation(
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
	explicit DimmingAnimation(
		const float &animation_length,
		const float &animation_speed,
		const sf::Texture &texture1,
		const sf::Texture &texture2);

	/**
	 * @brief Destructor
	 */
	~DimmingAnimation();


	/**
	 * @brief Gets the texture 1 frame.
	 *
	 * @param current_time The current time
	 *
	 * @return The texture 1 frame.
	 * 
	 * All r,g,b values are reduce to 0 (until 1/2*TotalTime)
	 * After that we set alpha value on 0 - image is transparent 
	 * 
	 */
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



	/**
	 * @brief Gets the texture 2 frame.
	 *
	 * @param current_time The current time
	 *
	 * @return The texture 2 frame.
	 * 
	 * Until 1/2*TotalTime that we set alpha value on 0 - image is transparent  
	 * Atter that all r,g,b values are increasing from 0 
	 */
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
 
};