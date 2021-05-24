#pragma once

#include "Animation.h"

class PixelAnimation : public Animation
{
public:
	PixelAnimation();
	explicit PixelAnimation(
		const float &animation_length,
		const float &animation_speed,
		std::vector<unsigned char> texture1_pixels, 
		std::vector<unsigned char> texture2_pixels);

	explicit PixelAnimation(
		const float &animation_length,
		const float &animation_speed,
		const sf::Texture &texture1,
		const sf::Texture &texture2);

	virtual ~PixelAnimation() = default;

	inline virtual const std::vector<unsigned char> &getTexture1Frame(const float &current_time) const = 0;
	inline virtual const std::vector<unsigned char> &getTexture2Frame(const float &current_time) const = 0;
	
	std::vector<unsigned char> getPixels1() const;
	std::vector<unsigned char> getPixels2() const;

	void setPixels1(std::vector<unsigned char> texture1_pixels);
	void setPixels2(std::vector<unsigned char> texture2_pixels);

protected:
	std::vector<unsigned char> m_pixels1;
	std::vector<unsigned char> m_pixels2;

private:
	
};