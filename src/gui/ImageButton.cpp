#include "../../include/gui/ImageButton.h"

ImageButton::ImageButton()
:Button() {}

ImageButton::ImageButton(const sf::Vector2f &pos, const sf::Vector2f &size,const int number)
    :Button(pos, size)
    {
        m_isChanged = false;
        m_shape.setOutlineThickness(5);
        m_shape.setOutlineColor(sf::Color(80,220,80));
        if(number == 1)
        {
             m_texture.loadFromFile("../res/images/1.png");
        }
        else
        {
             m_texture.loadFromFile("../res/images/2.png");    
        }

        m_spr.setTexture(m_texture);

        m_spr.setPosition(m_shape.getPosition().x, m_shape.getPosition().y);

        m_spr.setScale(static_cast<float>((m_shape.getSize().x) / (m_texture.getSize().x)), 
                static_cast<float>((m_shape.getSize().y) / (m_texture .getSize().y) ));
                
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
    target->draw(m_spr);
}

void ImageButton::update(sf::Vector2i mousePos, sf::Event &event)
{

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_shape.getGlobalBounds().contains(mousePos.x, mousePos.y ))
        {
            char const * lFilterPatterns[3] = { "*.png", "*.jpg","*.bmp"};
            
            char const * selection = tinyfd_openFileDialog("Select file", NULL, 3, lFilterPatterns, NULL, 0 );

            m_path = std::string(selection);

            if(selection != nullptr)
            {

                m_isChanged = true;

                m_texture.loadFromFile(std::string(selection));

                m_spr.setTexture(m_texture, true);
                
                m_spr.setPosition(m_shape.getPosition().x, m_shape.getPosition().y);
                
                m_spr.setScale(static_cast<float>((m_shape.getSize().x) / (m_texture.getSize().x)), 
                    static_cast<float>((m_shape.getSize().y) / (m_texture .getSize().y) ));
            }
          
        }   
        
}


std::string ImageButton::getPath()
{
    return m_path;
}

const bool ImageButton::isChanged() const
{
    return m_isChanged;
}

void ImageButton::changeRead()
{
    m_isChanged = false;
}

