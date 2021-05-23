#include "../../include/gui/AnimControlButton.h"

bool AnimControlButton::m_isAnimationActive = false;
unsigned int AnimControlButton::m_x = 50;
unsigned int AnimControlButton::m_y = 50;

AnimControlButton::AnimControlButton()
:
Button()
{}

AnimControlButton::AnimControlButton(const sf::Vector2f &pos)
: 
Button(pos, sf::Vector2f(static_cast<float>(m_x), static_cast<float>(m_y)) )
{
	m_texture.loadFromFile("../res/gfk/play_button.png");
	m_sprite.setColor( sf::Color(200,200,200) );
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(pos);
}

bool AnimControlButton::isAnimationActive() const
{
	return m_isAnimationActive;
}


void AnimControlButton::setAnimationActivity(const bool isActive)
{
	m_isAnimationActive = isActive;
}

void AnimControlButton::render(sf::RenderTarget *target) 
{
	Button::render(target);
	target->draw(this->m_sprite);
}	


void AnimControlButton::update(sf::Vector2i mousePos, sf::Event &event) 
{

	Button::update(mousePos, event);
}
