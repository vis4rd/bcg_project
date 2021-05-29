#pragma once

#include "Object.h"
/*
 *#include "Cnavas.h"? - obsuga animacji równocześnioe z obsługą buttonów? 
 */

class Panel : public Object
{

	public:

	Panel();
	Panel(const sf::Vector2f &pos, const sf::Vector2f &size);
	~Panel() = default;

	void update(sf::Vector2i mousePos, sf::Event &event) override;
	void render(sf::RenderTarget *target) override;

};
