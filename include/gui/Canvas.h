#pragma once

#include "AnimatedImage.h"
#include "../animation/ObjectAnimation.h"
#include "../animation/PixelAnimation.h"

class Canvas final
{
public:
	Canvas();
	Canvas(const sf::Vector2f &position, const sf::Vector2f &size);
	~Canvas() = default;

	void setAnimation(std::unique_ptr<ObjectAnimation> new_animation);
	void setAnimation(std::unique_ptr<PixelAnimation> new_animation);
	void setStartingImage(const sf::String &directory_path);
	void setEndingImage(const sf::String &directory_path);

	void setCurrentAnimationTime(const float &current_time);
	void setTotalAnimationTime(const float &seconds);
	void setAnimationPlayOn(const bool status);
	void setSize(const sf::Vector2f &new_size);
	void setPosition(const sf::Vector2f &new_position);

	void update(sf::Vector2i mousePos, sf::Event &event);
	void render(sf::RenderTarget *target);
	
protected:

private:
	void clearAnimation();///> Prepares Canvas for change of animation
	void clearStartingImage();///> Prepares Canvas for change of starting image
	void clearEndingImage();///> Prepares Canvas for change of finishing image

	sf::RenderTexture m_plane;
	sf::Sprite m_planeBody;

	std::unique_ptr<ObjectAnimation> m_objAnim;
	std::unique_ptr<PixelAnimation> m_pixAnim;
	enum AnimationType
	{
		NONE = 0,
		OBJ_ANIM = 1,
		PIX_ANIM = 2
	};
	unsigned short m_animType;
	std::unique_ptr<AnimatedImage> m_startingImage;
	std::unique_ptr<AnimatedImage> m_endingImage;
	std::unique_ptr<AnimatedImage> m_pixelImage;

	bool m_isAnimPlaying;
	float m_currentAnimTime; //in seconds
	float m_totalAnimTime; //in seconds
};
