#pragma once

#include "Button.h"

class TextButton : public Button
{
public:
	TextButton();
    explicit TextButton(const sf::Vector2f &pos, const sf::Vector2f &size, std::shared_ptr<sf::Font> font, const sf::String &label = sf::String());
    ~TextButton() =  default;

    const sf::String &getLabel() const;
    const sf::Text &getText() const;
    void setLabel(const sf::String &new_label);
    void setSize(const sf::Vector2f &new_size) override;

    void update(sf::Vector2i mousePos, sf::Event &event) override;
    void render(sf::RenderTarget *target) override;

protected:
	std::shared_ptr<sf::Font> m_font;
	sf::Text m_label;

private:
	void centerText();

};