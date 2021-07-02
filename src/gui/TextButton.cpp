#include "../../include/gui/TextButton.h"
#include "../../res/fonts/TerminusTTF.h"

TextButton::TextButton()
:
Button(),
m_font(nullptr),
m_label(sf::Text())
{
	m_label.setString("undefined");
	m_label.setCharacterSize(m_shape.getSize().y / 3.f);
	m_label.setFillColor(sf::Color::Black);
	this->centerText();
}

TextButton::TextButton(const sf::Vector2f &pos, const sf::Vector2f &size, std::shared_ptr<sf::Font> font, const sf::String &label)
:
Button(pos, size),
m_font(font),
m_label(sf::Text())
{
	if(m_font == nullptr)//if font wasn't given as parameter
	{
		m_font = std::make_shared<sf::Font>();
	}
	
	if(m_font->getInfo().family.empty())//if font was given, but without loading actual font
	{
		if(!m_font->loadFromFile("../res/fonts/Noir_regular.otf"))
		{
			//throw std::runtime_error("TextButton: Could not load \"res/fonts/Noir_regular.otf\" font.");
			if(!m_font->loadFromMemory(font_data, font_data_size))
			{
				throw std::runtime_error("TextButton: Could not load \"res/fonts/TerminusTTF\" font.");
			}
		}
	}

	m_label.setFont(*m_font);
	m_label.setStyle(sf::Text::Bold);
	m_label.setCharacterSize(m_shape.getSize().y / 3.f);
	if(!label.isEmpty())
	{
		m_label.setString(label);
	}
	else
	{
		m_label.setString("undefined");
	}
	m_label.setFillColor(sf::Color::Black);
	this->centerText();
}

const sf::String &TextButton::getLabel() const
{
	return m_label.getString();
}

const sf::Text &TextButton::getText() const
{
	return m_label;
}

void TextButton::setLabel(const sf::String &new_label)
{
	if(new_label.getSize() < 49)
	{
		m_label.setString(new_label);
		this->centerText();
	}
}

void TextButton::setSize(const sf::Vector2f &new_size)
{
	Button::setSize(new_size);
	this->centerText();
}

void TextButton::setPosition(const sf::Vector2f &new_pos)
{
	Button::setPosition(new_pos);
	this->centerText();
}

void TextButton::setFont(std::shared_ptr<sf::Font> new_font)
{
	if(new_font == nullptr)//if font wasn't given as parameter
	{
		throw std::runtime_error("TextButton: Cannot set the font to nullptr.");
	}
	else
	{
		if(new_font->getInfo().family.empty())//if font was given, but without loading actual font
		{
			m_font = new_font;
			if(!m_font->loadFromFile("../res/fonts/Noir_regular.otf"))
			{
				throw std::runtime_error("TextButton: Could not load \"res/fonts/Noir_regular.otf\" font.");
			}
			this->centerText();
		}
	}
}

void TextButton::setFontSize(const unsigned int &pixels)
{
	if(pixels > static_cast<unsigned int>(this->getSize().y))
	{
		m_label.setCharacterSize(static_cast<unsigned int>(this->getSize().y) - 3u);
	}
	else
	{
		m_label.setCharacterSize(pixels);
	}
	this->centerText();
}

void TextButton::update(sf::Vector2i mousePos, sf::Event &event)
{
	Button::update(mousePos, event);
}

void TextButton::render(std::shared_ptr<sf::RenderTarget> target)
{
	Button::render(target);
	if( (m_font != nullptr) &&
		!m_label.getString().isEmpty() &&
		(m_label.getFont() != nullptr) )
	{
		target->draw(m_label);
	}
}

//private member functions
void TextButton::centerText()
{
	m_label.setPosition(
    	m_shape.getPosition().x + (m_shape.getGlobalBounds().width / 2.f) - (m_label.getGlobalBounds().width / 1.817f),
    	m_shape.getPosition().y + (m_shape.getGlobalBounds().height / 2.f) - (m_label.getCharacterSize() / 1.4f)
    	);
}
