#include "../../include/gui/ImageButton.h"

ImageButton::ImageButton()
:Button() {
    
}

ImageButton::ImageButton(const sf::Vector2f &pos, const sf::Vector2f &size,const int number)
    :Button(pos, size)
    {
        m_shape.setOutlineThickness(5);
        m_shape.setOutlineColor(sf::Color(220,220,80));
        if(number == 1)
        {

        texture.loadFromFile("../res/images/1.png");
        }
        else
        {
        texture.loadFromFile("../res/images/2.png");    
        }

        spr.setTexture(texture);

        spr.setPosition(m_shape.getPosition().x, m_shape.getPosition().y);

        spr.setScale(static_cast<float>((m_shape.getSize().x) / (texture.getSize().x)), 
                static_cast<float>((m_shape.getSize().y) / (texture .getSize().y) ));
                
    }

ImageButton::ImageButton(const ImageButton &copy)
:
Button(copy)
{}


ImageButton::ImageButton(ImageButton &&source)
:
Button(source)
{}

void ImageButton::render(sf::RenderTarget *target)
{   
    target->draw(m_shape);
    target->draw(spr);
}

void ImageButton::update(sf::Vector2i mousePos, sf::Event &event)
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
        
        if(m_state == Button::state::ACTIVE)
        {
            char const * lFilterPatterns[3] = { "*.png", "*.jpg","*.bmp"};
            

            char const * selection = tinyfd_openFileDialog("Select file", "C:\\", 3, lFilterPatterns, NULL, 0 );
            if(selection != nullptr)
            {

            texture.loadFromFile(std::string(selection));

            spr.setTexture(texture, true);
            
            spr.setPosition(m_shape.getPosition().x, m_shape.getPosition().y);
            
            spr.setScale(static_cast<float>((m_shape.getSize().x) / (texture.getSize().x)), 
                static_cast<float>((m_shape.getSize().y) / (texture .getSize().y) ));
            }
          
        }   
        

}
