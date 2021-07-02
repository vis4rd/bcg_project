#include "../../include/gui/Panel.h"


Panel::Panel(const sf::Vector2f &pos, const sf::Vector2f &size)
:
Object(pos, size)
{
	m_shape.setFillColor( sf::Color(40,40,40) );
	m_shape.setOutlineThickness(-3.f);
	m_shape.setOutlineColor(sf::Color(90,90,90) );
}

void Panel::update(sf::Vector2i mousePos, sf::Event &event)
{
	return;
} 

void Panel::render(std::shared_ptr<sf::RenderTarget> target) 
{
	target->draw(m_shape);
}
