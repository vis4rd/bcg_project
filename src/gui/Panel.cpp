#include "../../include/gui/Panel.h"


Panel::Panel()
:
Object()
{}

Panel::Panel(const sf::Vector2f &pos, const sf::Vector2f &size)
:
Object(pos, size)
{
	m_shape.setFillColor( sf::Color(192,192,192) );
	m_shape.setOutlineThickness(3.f);
	m_shape.setOutlineColor(sf::Color(80,150,220) );
}

void Panel::update(sf::Vector2i mousePos, sf::Event &event)
{
	return;
} 

void Panel::render(sf::RenderTarget *target) 
{
	target->draw(m_shape);
}
