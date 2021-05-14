#pragma once

#include "../root/Root.h"

class Object
{
public:
	Object();

	//virtual void update(const float deltaTime, sf::Event event) = 0;
	virtual void render(sf::RenderTarget *target);

private:
	sf::RectangleShape *m_shape;
};