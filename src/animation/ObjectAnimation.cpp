#include "../../include/animation/ObjectAnimation.h"

ObjectAnimation::ObjectAnimation()
:
Animation(),
m_image1Start(sf::Transform()),
m_image2Start(sf::Transform()),
m_image1End(sf::Transform()),
m_image2End(sf::Transform())
{ }

ObjectAnimation::ObjectAnimation(
	const float &animation_length,
	const float &animation_speed,
	const sf::Transform &image1start,
	const sf::Transform &image2start,
	const sf::Transform &image1end,
	const sf::Transform &image2end)
:
Animation(animation_length, animation_speed),
m_image1Start(image1start),
m_image2Start(image2start),
m_image1End(image1end),
m_image2End(image2end)
{

}