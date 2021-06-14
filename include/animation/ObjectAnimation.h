#pragma once

#include "Animation.h"
#include "../util/ExtendedMath.h"

/**
 * @brief Base class of every animation, based on transformations of textures 
 */
class ObjectAnimation : public Animation
{
public:
	/**
	 * Default constructor
	 */
	ObjectAnimation();

	/**
	 * @brief Constructor settings all variables of animatiom
	 *
	 * @param animation_length 	Length of animation 
	 * @param animation_speed  	Speed of animation
	 * @param image1start 		Matrix of first starting image
	 * @param image2start 		Matrix of second starting image
	 * @param image1end 		Matrix of first ending image
	 * @param image2end 		Matrix of secend ending image
	 */
	explicit ObjectAnimation(
		const float &animation_length,
		const float &animation_speed,
		const em::Matrix4f &image1start,
		const em::Matrix4f &image2start,
		const em::Matrix4f &image1end,
		const em::Matrix4f &image2end);

	/**
	 * @brief Destroys the object.
	 */
	virtual ~ObjectAnimation() = default;


	/**
	 * @brief      pure virtual method responisble for animations on first image
	 *
	 * @param[in]  current_time  The current time
	 *
	 * @return     Frame of first image.
	 */
	inline virtual const em::Matrix4f getImage1Frame(const float &current_time) const = 0;
	
	/**
	 * @brief 	    pure virtual method responsible for animations on second image
	 *
	 * @param 		current_time The current time
	 *
	 * @return 		Frame of second image.
	 */
	inline virtual const em::Matrix4f getImage2Frame(const float &current_time) const = 0;

	/**
	 * @brief Getter for the starting transform for image 1.
	 *
	 * @return m_image1Start
	 */
	const em::Matrix4f &getStartingTransform1() const;
	
	/**
	 * @brief Getter for the starting transform for image 2.
	 *
	 * @return m_image2Start
	 */
	const em::Matrix4f &getStartingTransform2() const;
	
	/**
	 * @brief Getter for the ending transform for image 1.
	 *
	 * @return m_image1End
	 */
	const em::Matrix4f &getEndingTransform1() const;
	
	/**
	 * @brief Getter for the ending transform for image 2.
	 *
	 * @return m_image2End
	 */
	const em::Matrix4f &getEndingTransform2() const;

	/**
	 * @brief Setter for the starting transform for image 1.
	 *
	 * @param im1_start The im 1 start
	 */
	void setStartingTransform1(const em::Matrix4f &im1_start);
	
	/**
	 * @brief Setter for the starting transform for image 2.
	 *
	 * @param im2_start The im 2 start
	 */
	void setStartingTransform2(const em::Matrix4f &im2_start);
	
	/**
	 * @brief Setter for the ending transform for image 1.
	 *
	 * @param im1_end The im 1 end
	 */
	void setEndingTransform1(const em::Matrix4f &im1_end);
	
	/**
	 * @brief Setter for the ending transform for image 2.
	 *
	 * @param im2_end The im 2 end
	 */
	void setEndingTransform2(const em::Matrix4f &im2_end);

protected:
	em::Matrix4f m_image1Start;	///> starting position of image1
	em::Matrix4f m_image2Start;	///> starting position of image2
	em::Matrix4f m_image1End;	///> finishing position of image1
	em::Matrix4f m_image2End;	///> finishing position of image2
	
};