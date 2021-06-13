#include "../../include/gui/SaveButton.h"

SaveButton::SaveButton()
:Button() {}

SaveButton::SaveButton(const sf::Vector2f &pos, const sf::Vector2f &size)
:Button(pos, size)
{
    m_shape.setOutlineThickness(0.f);
    m_shape.setOutlineColor( sf::Color::Black );
    m_texture.loadFromFile("../res/images/save_icon.png");
    m_spr.setTexture(m_texture);
    m_spr.setPosition(m_shape.getPosition().x, m_shape.getPosition().y);
    m_spr.setScale(static_cast<float>((m_shape.getSize().x) / (m_texture.getSize().x)), 
            static_cast<float>((m_shape.getSize().y) / (m_texture .getSize().y) ));
            
}

SaveButton::SaveButton(const SaveButton &copy)
:
Button(copy)
{}


SaveButton::SaveButton(SaveButton &&source)
:
Button(source)
{}

void SaveButton::render(sf::RenderTarget *target)
{   
    target->draw(m_shape);
    target->draw(m_spr);
}

void SaveButton::update(sf::Vector2i mousePos, sf::Event &event)
{
    if(m_state != Button::state::LOCKED)
    {
        if(m_shape.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            m_state = Button::state::HOVER;

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                m_state = Button::state::ACTIVE;
            }
        }
        else
        {
            m_state = Button::state::IDLE;
        }
        
        if(m_state == Button::state::IDLE)
        {
            m_shape.setFillColor( /*sf::Color(30,30,30)*/sf::Color::Transparent );
        }
        else if(m_state == Button::state::HOVER)
        {
            m_shape.setFillColor( sf::Color(255, 255, 255, 50) );
        }
        else
        {
            m_shape.setFillColor( sf::Color(0,0,0) );
        }
    }       
}


