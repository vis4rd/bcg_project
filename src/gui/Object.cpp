#include "../../include/gui/Object.h"

Object::Object(const sf::Vector2f &pos, const sf::Vector2f &size)
{
	this->m_shape.setPosition(pos);
	this->m_shape.setSize(size);
	this->m_shape.setFillColor(sf::Color::Transparent);
	this->m_shape.setOutlineThickness(-2.f);
}

Object::Object(const Object &copy) 
{
	this->m_shape = copy.m_shape;
}

Object::Object(Object &&source) 
{
	this->m_shape = std::move(source.m_shape);
}

const sf::Vector2f &Object::getPosition() const 
{
	return this->m_shape.getPosition();
}

const sf::Vector2f &Object::getSize() const 
{
	return this->m_shape.getSize();
}

const sf::RectangleShape &Object::getShape() const 
{
	return this->m_shape;
}

void Object::setPosition(const sf::Vector2f &pos) 
{
	this->m_shape.setPosition(pos);
}

void Object::setSize(const sf::Vector2f &size) 
{
	this->m_shape.setSize(size);
}