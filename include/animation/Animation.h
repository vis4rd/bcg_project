#pragma once

#include "../root/Root.h"

class Animation
{
public:
	Animation();
	explicit Animation(const float &animation_length, const float &animation_speed);
	virtual ~Animation() = default;

	virtual const float &getAnimationLength() const; //in seconds
	virtual const float &getAnimationSpeed() const;

	virtual void setAnimationLength(const float &seconds);
	virtual void setAnimationSpeed(const float &speed_factor);

protected:
	float m_totalTime; //in ms
	float m_currentTime; // interval [ 0 ; 1 ]
	float m_speedFactor; // x < 1 : slower, x > 1 faster
	
};