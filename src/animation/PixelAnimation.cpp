#include "../../include/animation/PixelAnimation.h"

PixelAnimation::PixelAnimation()
:
Animation(),
m_pixels1({}),
m_pixels2({})
{ }

PixelAnimation::PixelAnimation(
	const float &animation_length, 
	const float &animation_speed,
	std::vector<unsigned char> texture1_pixels, 
	std::vector<unsigned char> texture2_pixels)
:
Animation(animation_length, animation_speed),
m_pixels1(texture1_pixels),
m_pixels2(texture2_pixels)
{
	std::cout << "Wektor 1: " << std::endl;
	for(auto &it : m_pixels1)
		std::cout << it << " ";
	std::cout << std::endl << std::endl;

	std::cout << "Wektor 2: " << std::endl;
	for(auto &it : m_pixels2)
		std::cout << it << " ";
	std::cout << std::endl << std::endl;
}

PixelAnimation::PixelAnimation(
	const float &animation_length,
	const float &animation_speed,
	const sf::Texture &texture1,
	const sf::Texture &texture2)
:
Animation(animation_length, animation_speed)
{
	if(texture1.getSize() != sf::Vector2u(0u, 0u))
	{
		const sf::Image &temp = texture1.copyToImage();
		const sf::Uint8 *pix = temp.getPixelsPtr();
		unsigned size = texture1.getSize().x * texture1.getSize().y * 3;
		for(unsigned i = 0; i < size; i++)
		{
			m_pixels1.push_back(pix[i]);
		}
	}
	else
	{
		m_pixels1 = {};
	}
	

	if(texture2.getSize() != sf::Vector2u(0u, 0u))
	{
		const sf::Image &temp = texture1.copyToImage();
		const sf::Uint8 *pix = temp.getPixelsPtr();
		unsigned size = texture2.getSize().x * texture2.getSize().y * 3;
		for(unsigned i = 0; i < size; i++)
		{
			m_pixels1.push_back(pix[i]);
		}
	}
	else
	{
		m_pixels2 = {};
	}
}

std::vector<unsigned char> PixelAnimation::getPixels1() const
{
	return m_pixels1;
}

std::vector<unsigned char> PixelAnimation::getPixels2() const
{
	return m_pixels2;
}

void PixelAnimation::setPixels1(std::vector<unsigned char> texture1_pixels)
{
	m_pixels1 = texture1_pixels;
}

void PixelAnimation::setPixels2(std::vector<unsigned char> texture2_pixels)
{
	m_pixels2 = texture2_pixels;
}