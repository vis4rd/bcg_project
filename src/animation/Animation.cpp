#include "../../include/animation/Animation.h"

Animation::Animation()
:
Animation(0.f, 0.f)
{ }

Animation::Animation(const float &animation_length, const float &animation_speed)
:
m_totalTime(animation_length),
m_currentTime(0.f),
m_speedFactor(animation_speed)
{ }

const float &Animation::getAnimationLength() const
{
	return m_totalTime;
}

const float &Animation::getAnimationSpeed() const
{
	return m_speedFactor;
}

void Animation::setAnimationLength(const float &seconds)
{
	if(seconds < 0.f)
	{
		throw std::runtime_error("Animation::setAnimationLength(): Length cannot have negative value.");
	}
	else
	{
		m_totalTime = seconds;
	}
}

void Animation::setAnimationSpeed(const float &speed_factor)
{
	if(fabs(speed_factor) < 1e-7f)
	{
		throw std::runtime_error("Animation::setAnimationSpeed(): Speed cannot have value of 0.");
	}
	else
	{
		m_speedFactor = speed_factor;
	}
}
