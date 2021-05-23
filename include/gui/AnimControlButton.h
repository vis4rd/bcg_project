#pragma once

#include "Button.h"


class AnimControlButton: public Button
{

public:
    //constructors and dectructors
	AnimControlButton();
	AnimControlButton(const sf::Vector2f &pos);
	~AnimControlButton() = default;
    
    //getter
	bool isAnimationActive() const;

    //render and update
	void render(sf::RenderTarget *target) override;
	void update(sf::Vector2i mousePos, sf::Event &event) override;

    //setter
	static void setAnimationActivity(const bool isActive);

protected:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	static unsigned int m_x;
	static unsigned int m_y;

private:
	static bool m_isAnimationActive;

	
};
