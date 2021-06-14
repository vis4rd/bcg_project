#pragma once

#include "PixelAnimation.h"


/**
 * @brief      This class performs animation with alpha oppasity manipulation.
 * 			 	First image slowly fading and became transparent,
 * 			 	the second one is apperaing in same time.
 */
class AlfaAnimation : public PixelAnimation
{
	public:

	/**
	 * Default constructor
	 */
	AlfaAnimation();

	/**
	 * @brief      The constructor with settings of animation
	 *
	 * @param      animation_length  The animation length
	 * @param      animation_speed   The animation speed
	 * @param      texture1_pixels   The texture of start image
	 * @param      texture2_pixels   The texture of end image
	 */
	explicit AlfaAnimation(
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
	explicit AlfaAnimation(
		const float &animation_length,
		const float &animation_speed,
		const sf::Texture &texture1,
		const sf::Texture &texture2);

	/**
	 * @brief      Destructor
	 */
	~AlfaAnimation();



	/**
	 * @brief      Returns how texture of start image should look.
	 *
	 * @param      current_time  The current time
	 *
	 * @return     The first image look in specific time.
	 */
	inline const std::vector<unsigned char> getTexture1Frame(const float &current_time) const override
	{
		std::vector<unsigned char> temp = m_pixels1;
		for(unsigned i=3; i<temp.size(); i+=4)
		{
			temp[i] = static_cast<unsigned char>( static_cast<float>(temp[i]) - (static_cast<float>(temp[i]) * (current_time/m_totalTime)) );
		}
			
		return temp;
	}


	/**
	 * @brief      Returns how texture of end image should look.
	 *
	 * @param      current_time  The current time
	 *
	 * @return     The end image look in specific time.
	 */
	inline const std::vector<unsigned char> getTexture2Frame(const float &current_time) const override
	{
		std::vector<unsigned char> temp = m_pixels2;
		for(unsigned i=3; i<temp.size(); i+=4)
		{
			temp[i] = static_cast<unsigned char>( (static_cast<float>(temp[i]) * (current_time/m_totalTime)) ) ;
		}
			
		return temp;
	} 
 
};