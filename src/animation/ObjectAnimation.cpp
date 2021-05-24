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

const sf::Transform &ObjectAnimation::getStartingTransform1() const
{
	return m_image1Start;
}

const sf::Transform &ObjectAnimation::getStartingTransform2() const
{
	return m_image2Start;
}

const sf::Transform &ObjectAnimation::getEndingTransform1() const
{
	return m_image1End;
}

const sf::Transform &ObjectAnimation::getEndingTransform2() const
{
	return m_image2End;
}

void ObjectAnimation::setStartingTransform1(const sf::Transform &im1_start)
{
	m_image1Start = im1_start;
}

void ObjectAnimation::setStartingTransform2(const sf::Transform &im2_start)
{
	m_image2Start = im2_start;
}

void ObjectAnimation::setEndingTransform1(const sf::Transform &im1_end)
{
	m_image1End = im1_end;
}

void ObjectAnimation::setEndingTransform2(const sf::Transform &im2_end)
{
	m_image2End = im2_end;
}