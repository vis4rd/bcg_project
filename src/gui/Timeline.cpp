#include "../../include/gui/Timeline.h"



Timeline::Timeline()
:
Button()
{
    m_shape.setOutlineThickness(1);
    m_shape.setOutlineColor(sf::Color::White);
    m_ONOFF = false;
}



Timeline::Timeline(sf::Vector2f pos, sf::Vector2f size)
:
Button(pos,size)
{
    m_length = size.x;
    m_body = new sf::VertexArray(sf::Quads);

    m_cursor = sf::CircleShape(8);
    m_cursor.setFillColor(sf::Color(220,220,80));
    m_cursor.setPosition(pos + sf::Vector2f(-5.f , - 9.f) ); 
    m_cursor.setOutlineColor( sf::Color(20,20,20) );
    m_cursor.setOutlineThickness(3.f);

    m_covered.setPosition( pos + sf::Vector2f( -3.f, -3.f) );
    m_covered.setFillColor( sf::Color(200,220,60) );
    m_covered.setSize( sf::Vector2f( m_cursor.getPosition().x - m_covered.getPosition().x  , 4.f) );

    m_box.setPosition(pos);
    m_box.setSize(size);
    m_box.setFillColor(sf::Color::Black);
    m_box.setOutlineColor(sf::Color(120,120,120));
    m_box.setOutlineThickness(4.f);
}

bool Timeline::isPlay() const
{
    return m_ONOFF;
}

void Timeline::play()
{
    m_ONOFF = true;
}

void Timeline::pause()
{
    m_ONOFF = false;
}

void Timeline::update(sf::Vector2i mousePos, sf::Event &event)
{   
    if(this->m_box.getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y)))
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->pause();
            sf::Vector2f where = (sf::Vector2f(mousePos.x, mousePos.y) - this->m_box.getPosition());
            this->setCursorPosition(where.x);
        }
    }
}

void Timeline::render(sf::RenderTarget *target) 
{
    if ( this->isFinished() == false && this->isPlay() )
    {
        this->m_cursor.setPosition( m_cursor.getPosition() + sf::Vector2f(2.f, 0)  );
        m_covered.setSize( sf::Vector2f( m_cursor.getPosition().x - m_covered.getPosition().x  , 8.f) );

    }

    target->draw(this->m_box);
    target->draw(*this->m_body);
    target->draw(this->m_covered);
    target->draw(this->m_cursor);
}

void Timeline::setCursorPosition(float localX)
{
    m_cursor.setPosition( this->getPosition() + sf::Vector2f(localX, -9.f) );
    m_covered.setSize( sf::Vector2f( m_cursor.getPosition().x - m_covered.getPosition().x  , 8.f) );
}

void Timeline::ON_OFF()
{
    m_ONOFF = !m_ONOFF;
}

bool Timeline::isFinished() 
{
    if ( m_cursor.getPosition().x >= m_box.getPosition().x + m_length - 10.f )
    {
        this->pause();
        return true;
    }  
    return false;
}