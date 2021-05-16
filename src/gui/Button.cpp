#include "../../include/gui/Button.h"

    Button::Button()
    :Object(), m_state(Button::state::IDLE)
    {}

    Button::Button(const sf::Vector2f &pos, const sf::Vector2f &size)
    :Object(pos, size), m_state(Button::state::IDLE)
    {}
    
    //getters
    const unsigned short Button::getState()
    {
        return m_state;
    }

    //setters
    void Button::setState(unsigned short newState )
    {
        m_state = newState;
    }

    //check and update methods
    bool Button::isPressed()
    {
        if(m_state == Button::state::ACTIVE)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void Button::update(sf::Vector2i mousePos)
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
            m_shape.setFillColor( sf::Color(200,200,200) );
            m_shape.setOutlineColor(sf::Color::Black);
            m_shape.setOutlineThickness(5);

        }

        else if(m_state == Button::state::HOVER)
        {
            m_shape.setFillColor( sf::Color(100,100,100) );
            m_shape.setOutlineColor(sf::Color::Black);
            m_shape.setOutlineThickness(5);

        }

        else
        {
            m_shape.setFillColor( sf::Color(100,200,100) );
            m_shape.setOutlineColor(sf::Color::Black);
            m_shape.setOutlineThickness(5);
        }

    }

    void Button::render(sf::RenderTarget *target)
    {
        target->draw(m_shape);
    }
