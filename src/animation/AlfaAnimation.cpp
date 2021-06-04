#include "../../include/animation/AlfaAnimation.h"


AlfaAnimation::AlfaAnimation()
:
PixelAnimation()
{

}
	
AlfaAnimation::AlfaAnimation(
	const float &animation_length,
	const float &animation_speed,
	std::vector<unsigned char> texture1_pixels, 
	std::vector<unsigned char> texture2_pixels)
:
PixelAnimation(animation_length, animation_speed, texture1_pixels, texture2_pixels)
{
}

AlfaAnimation::AlfaAnimation(
	const float &animation_length,
	const float &animation_speed,
	const sf::Texture &texture1,
	const sf::Texture &texture2)
:
PixelAnimation(animation_length, animation_speed, texture1, texture2)
{
}

AlfaAnimation::~AlfaAnimation()
{
	m_pixels1.clear();
	m_pixels2.clear();
}

