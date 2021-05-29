#include "../../include/animation/ObjectAnimation.h"

ObjectAnimation::ObjectAnimation()
:
Animation(),
m_image1Start(em::Matrix4f()),
m_image2Start(em::Matrix4f()),
m_image1End(em::Matrix4f()),
m_image2End(em::Matrix4f())
{ }

ObjectAnimation::ObjectAnimation(
	const float &animation_length,
	const float &animation_speed,
	const em::Matrix4f &image1start,
	const em::Matrix4f &image2start,
	const em::Matrix4f &image1end,
	const em::Matrix4f &image2end)
:
Animation(animation_length, animation_speed),
m_image1Start(image1start),
m_image2Start(image2start),
m_image1End(image1end),
m_image2End(image2end)
{

}

const em::Matrix4f &ObjectAnimation::getStartingTransform1() const
{
	return m_image1Start;
}

const em::Matrix4f &ObjectAnimation::getStartingTransform2() const
{
	return m_image2Start;
}

const em::Matrix4f &ObjectAnimation::getEndingTransform1() const
{
	return m_image1End;
}

const em::Matrix4f &ObjectAnimation::getEndingTransform2() const
{
	return m_image2End;
}

void ObjectAnimation::setStartingTransform1(const em::Matrix4f &im1_start)
{
	m_image1Start = im1_start;
}

void ObjectAnimation::setStartingTransform2(const em::Matrix4f &im2_start)
{
	m_image2Start = im2_start;
}

void ObjectAnimation::setEndingTransform1(const em::Matrix4f &im1_end)
{
	m_image1End = im1_end;
}

void ObjectAnimation::setEndingTransform2(const em::Matrix4f &im2_end)
{
	m_image2End = im2_end;
}
