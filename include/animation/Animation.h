#pragma once

#include "../root/Root.h"


/**
 * @brief Base class of all animation
 */
class Animation
{
public:
	/**
	 * Default constructor
	 */
	Animation();
	
	/**
	 * @brief Contructor settings animation length and speed
	 *
	 * @param animation_length The animation length
	 * @param animation_speed The animation speed
	 */
	explicit Animation(const float &animation_length, const float &animation_speed);
	
	/**
	 * @brief Destructor
	 */
	virtual ~Animation() = default;

	/**
	 * @brief Getter of the leangth of animation.
	 *
	 * @return The animation length.
	 */
	virtual const float &getAnimationLength() const; //in seconds
	
	/**
	 * @brief Getter of the speed of animation.
	 *
	 * @return The animation speed.
	 */
	virtual const float &getAnimationSpeed() const;

	/**
	 * @brief Setter of the animation length.
	 *
	 * @param seconds time in seconds
	 */
	virtual void setAnimationLength(const float &seconds);
	
	/**
	 * @brief Setter of the animation speed.
	 *
	 * @param speed_factor new speed value
	 */
	virtual void setAnimationSpeed(const float &speed_factor);

protected:
	float m_totalTime; 
	float m_currentTime; 
	float m_speedFactor; 
	
};
