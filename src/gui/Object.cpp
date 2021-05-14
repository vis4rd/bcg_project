#include "../../include/gui/Object.h"

Object::Object()
{
	m_shape = new sf::RectangleShape(sf::Vector2f(20.f, 20.f));
	m_shape->setFillColor(sf::Color::White);
}

void Object::render(sf::RenderTarget *target)
{
	if(m_shape)
		target->draw(*m_shape);
}