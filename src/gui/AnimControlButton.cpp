#include "../../include/gui/AnimControlButton.h"

AnimControlButton::AnimControlButton()
:
Button()
{
    m_shape.setOutlineThickness(0);
}

AnimControlButton::AnimControlButton(const sf::Vector2f &pos)
: 
Button(pos, sf::Vector2f(40.f, 40.f) )
{
    m_shape.setOutlineThickness(0);
	m_texture.loadFromFile("../res/images/play_button.png");
	m_sprite.setColor( sf::Color(250,250,250) );
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(pos);
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
