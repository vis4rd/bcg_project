#pragma once

#include "../root/Root.h"

class Object
{
public:
	Object();

	virtual void update(const float deltaTime) = 0;
	virtual void render(sf::RenderTarget *target) = 0;

private:
	std::unique_ptr<sf::RectangleShape> m_shape;
};