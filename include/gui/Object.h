#pragma once

#include "../root/Root.h"

class Object
{
public:
	
	Object(const sf::Vector2f &pos = sf::Vector2f(0.f, 0.f), const sf::Vector2f &size = sf::Vector2f(0.f, 0.f));
	Object(const Object &copy);
	Object(Object &&source);
	virtual ~Object() = default;

	//getters/setters/checkers
	const sf::Vector2f &getPosition() const;
	const sf::Vector2f &getSize() const;
	sf::RectangleShape &getShape();


	void setPosition(const sf::Vector2f &pos);
	void setSize(const sf::Vector2f &size);


	virtual void render(sf::RenderTarget *target) = 0;

	virtual void update(sf::Vector2i mousePos, sf::Event &event) = 0;

protected:
	sf::RectangleShape m_shape;

private:

};