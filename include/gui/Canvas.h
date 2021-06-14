#pragma once

#include "AnimatedImage.h"
#include "../animation/ObjectAnimation.h"
#include "../animation/PixelAnimation.h"

/**
 * Class handling image drawing and applying animations
 */
class Canvas final
{
public:
	/**
	 * Default constructor
	 */
	Canvas();

	/**
	 * @brief Constructor setting the position and the size of the Canvas
	 *
	 * @param position The position of the Canvas
	 * @param size The size of the Canvas
	 */
	Canvas(const sf::Vector2f &position, const sf::Vector2f &size);

	/**
	 * @brief Default destructor
	 */
	~Canvas() = default;

	/**
	 * @brief Sets the animation type to deriving of ObjectAnimation
	 *
	 * @param new_animation The new animation
	 */
	void setAnimation(std::unique_ptr<ObjectAnimation> new_animation);

	/**
	 * @brief Sets the animation type to deriving of PixelAnimation
	 *
	 * @param new_animation The new animation
	 */
	void setAnimation(std::unique_ptr<PixelAnimation> new_animation);

	/**
	 * @brief Sets the starting image of the animation
	 *
	 * @param directory_path The directory path to image
	 */
	void setStartingImage(const sf::String &directory_path);

	/**
	 * @brief Sets the ending image of the animation
	 *
	 * @param directory_path The directory path to image
	 */
	void setEndingImage(const sf::String &directory_path);

	/**
	 * @brief Sets the current time of the chosen animation
	 *
	 * @param current_time New current time of the animation (ranges from 0 to total time of the animation)
	 */
	void setCurrentAnimationTime(const float &current_time);

	/**
	 * @brief Sets the current progress of the chosen animation
	 *
	 * @param current_progress The current progress (ranges from 0 to 1)
	 */
	void setCurrentAnimationProgress(const float &current_progress);

	/**
	 * @brief Sets the total time of the animation (is usually is given by Timeline)
	 *
	 * @param seconds The total time of the animation in seconds
	 */
	void setTotalAnimationTime(const float &seconds);

	/**
	 * @brief Sets the animation status to true or false
	 *
	 * @param status The new play status of the animation
	 */
	void setAnimationPlayOn(const bool status);

	/**
	 * @brief Sets the size of the Canvas
	 *
	 * @param new_size The new size
	 */
	void setSize(const sf::Vector2f &new_size);

	/**
	 * @brief Sets the position of the Canvas
	 *
	 * @param new_position The new position relative to window
	 */
	void setPosition(const sf::Vector2f &new_position);

	/**
	 * @brief Getter to texture which the animation is rendered to
	 *
	 * @return The target texture of drawn animation
	 */
	sf::RenderTexture& getPlane();

	/**
	 * @brief Updates the animation when it's supposed to be played
	 *
	 * @param mousePos The mouse position relative to the window
	 * @param event The event reference handling all events in the window
	 */
	void update(sf::Vector2i mousePos, sf::Event &event);

	/**
	 * @brief Renders the animation to the target
	 *
	 * @param target The target which Canvas' object is rendered to
	 */
	void render(sf::RenderTarget *target);

	/**
	 * @brief Getter to the total time given to the Canvas
	 *
	 * @return The total animation time in seconds
	 */
	const float& getTotalTime();  
	
protected:

private:
	void clearAnimation();///> Prepares Canvas for the change of animation
	void clearStartingImage();///> Prepares Canvas for the change of starting image
	void clearEndingImage();///> Prepares Canvas for the change of finishing image

	sf::RenderTexture m_plane;///> Texture which everything is rendered to
	sf::Sprite m_planeBody;///> Sprite to which the texture is applied to

	std::unique_ptr<ObjectAnimation> m_objAnim;///> Pointer to ObjectAnimation derived object
	std::unique_ptr<PixelAnimation> m_pixAnim;///> Pointer to PixelAnimation derived object
	enum AnimationType
	{
		NONE = 0,
		OBJ_ANIM = 1,
		PIX_ANIM = 2
	};
	unsigned short m_animType;///> Specifier of animation type
	std::unique_ptr<AnimatedImage> m_startingImage;///> Starting image of ObjectAnimations
	std::unique_ptr<AnimatedImage> m_endingImage;///> Ending image of ObjectAnimations
	std::unique_ptr<AnimatedImage> m_pixelImageIn;///> Starting image of PixelAnimations
	std::unique_ptr<AnimatedImage> m_pixelImageOut;///> Ending image of PixelAnimations

	bool m_isAnimPlaying;///> Flag defining whether animation is being played or not
	float m_currentAnimTime;///> Current animation time
	float m_totalAnimTime;///> Total animation time
};
