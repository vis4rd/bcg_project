#include "../../include/gui/ImageButton.h"

ImageButton::ImageButton()
:Button() {}

ImageButton::ImageButton(const sf::Vector2f &pos, const sf::Vector2f &size)
:Button(pos, size)
{
    m_isChanged = false;
    m_shape.setOutlineThickness(5);
    m_shape.setOutlineColor(sf::Color::White);
    m_texture.loadFromFile("../res/images/placeholder.png");
    m_texture.setSmooth(false);

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
        char const *file_extensions[3] = { "*.png", "*.jpg","*.bmp"};
        char const *path = tinyfd_openFileDialog("Select file", NULL, 3, file_extensions, NULL, 0 );

        if(path != nullptr)
        {
            m_path = std::string(path);
            m_isChanged = true;
            m_texture.loadFromFile(m_path);

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
