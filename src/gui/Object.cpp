#include "../../include/gui/Object.h"



/*
void Object::render(sf::RenderTarget *target)
{
	if(m_m_shape)
		target->draw(*m_m_shape);
}
*/
Object::Object(const sf::Vector2f &pos, const sf::Vector2f &size)
:
stateCode(0u)
{
	this->m_shape.setPosition(pos);
	this->m_shape.setSize(size);
	this->m_shape.setFillColor(sf::Color::Transparent);
	//this->m_shape.setOutlineColor(Theme::getScheme()["foreground"]);
	this->m_shape.setOutlineThickness(-2.f);
}

Object::Object(const Object &copy) 
{
	this->m_shape = copy.m_shape;
	this->stateCode = copy.stateCode;
}

Object::Object(Object &&source) 
{
	this->m_shape = std::move(source.m_shape);
	this->stateCode = std::move(source.stateCode);
}

Object::~Object()
{

}

const sf::Vector2f &Object::getPosition() const 
{
	return this->m_shape.getPosition();
}

const sf::Vector2f &Object::getSize() const 
{
	return this->m_shape.getSize();
}

const sf::RectangleShape Object::getShape() const 
{
	return this->m_shape;
}

const unsigned short &Object::getCode() const
{
	return this->stateCode;
}

void Object::setPosition(const sf::Vector2f &pos) 
{
	this->m_shape.setPosition(pos);
}

void Object::setSize(const sf::Vector2f &size) 
{
	this->m_shape.setSize(size);
}