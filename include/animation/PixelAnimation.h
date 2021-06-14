#pragma once

#include "Animation.h"


/**
 * @brief Base class of every animation based on transformations on pixels
 */
class PixelAnimation : public Animation
{
public:
	/**
	 * Default constructor
	 */
	PixelAnimation();

	/**
	 * @brief Constructor settings parameters of animation
	 *
	 * @param animation_length 	Length of animation
	 * @param animation_speed 	Speed of animation
	 * @param texture1_pixels 	Texture of first image
	 * @param texture2_pixels 	Texture of second image
	 */
	 explicit PixelAnimation(
        const float &animation_length,
        const float &animation_speed,
        std::vector<unsigned char> texture1_pixels, 
        std::vector<unsigned char> texture2_pixels);

	/**
	 * @brief Constructor settings parameters of animation
	 *
	 * @param animation_length 	Length of animation
	 * @param animation_length 	Speed of animation
	 * @param texture1_pixels 	Texture of first image
	 * @param texture2_pixels 	Texture of second image
	 */
	  explicit PixelAnimation(
        const float &animation_length,
        const float &animation_speed,
        const sf::Texture &texture1,
        const sf::Texture &texture2);

	/**
	 * @brief Destructor.
	 */
	virtual ~PixelAnimation() = default;

	/**
	 * @brief 		Calculations of proper pixel sequnces depending from given time
	 *
	 * @param 		current_time The current time
	 *
	 * @return 		frame that first image adopts
	 */
	inline virtual const std::vector<unsigned char> getTexture1Frame(const float &current_time) const = 0;
	
	/**
	 * @brief 		Calculations of proper pixel sequnces depending from given time
	 *
	 * @param 		current_time The current time
	 *
	 * @return 		frame that second image adopts
	 */
	inline virtual const std::vector<unsigned char> getTexture2Frame(const float &current_time) const = 0;
	
	/**
	 * @brief 		Getter of the pixels of first image.
	 *
	 * @return 		vector of pixels of first image.
	 */
	std::vector<unsigned char> getPixels1() const;
	
	/**
	 * @brief 		Getter of the pixels of second image.
	 *
	 * @return 		vector of pixels of second image.
	 */
	std::vector<unsigned char> getPixels2() const;

	/**
	 * @brief 		Setter of the first image.
	 *
	 * @param texture1_pixels 	vector of pixels
	 */
	void setPixels1(std::vector<unsigned char> texture1_pixels);
	
	/**
	 * @brief 		Setter of the second image.
	 *
	 * @param texture1_pixels 	vector of pixels
	 */
	void setPixels2(std::vector<unsigned char> texture2_pixels);

	protected:
	std::vector<unsigned char> m_pixels1;
	std::vector<unsigned char> m_pixels2;
	
};