#pragma once

#include "Button.h"

class SaveButton : public Button
{
public:

	SaveButton();
	SaveButton(const sf::Vector2f &pos, const sf::Vector2f &size);
	SaveButton(const SaveButton &copy);
	SaveButton(SaveButton &&source);
	void render(sf::RenderTarget *target) override;
	void update(sf::Vector2i mousePos, sf::Event &event) override;

private:
	sf::Sprite m_spr;
	sf::Texture m_texture;
};	