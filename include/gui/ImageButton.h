#pragma once

#include "Button.h"

class ImageButton : public Button
{
public:

	ImageButton();
	ImageButton(const sf::Vector2f &pos, const sf::Vector2f &size, const int number);
	ImageButton(const ImageButton &copy);
	ImageButton(ImageButton &&source);
	void render(sf::RenderTarget *target) override;
	void update(sf::Vector2i mousePos, sf::Event &event) override;

private:
	sf::Sprite m_spr;
	sf::Texture m_texture;
};	