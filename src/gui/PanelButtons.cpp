#include "../../include/gui/PanelButtons.h"

PanelButton::PanelButton()
:Panel()
{}

PanelButton::PanelButton(const sf::Vector2f &pos, const sf::Vector2f &size)
:
Panel(pos,size)
{
    m_imageUp = new ImageButton(sf::Vector2f(pos.x + 10,pos.y + 10 ), sf::Vector2f(size.x - 20,size.y/4), 1);
    m_imageDown = new ImageButton(sf::Vector2f(pos.x + 10 , pos.y + 30 + size.y/4.f), sf::Vector2f(size.x - 20,size.y/4), 2);

    font = std::make_shared<sf::Font>();
    

    m_dropdownUp = new DropdownList(sf::Vector2f(pos.x + 20, pos.y + 50 + size.y/2), sf::Vector2f(size.x - 40, size.y/14), font, sf::String("BASIC"));
    m_dropdownDown = new DropdownList(sf::Vector2f(pos.x + 20, pos.y + size.y/14 + size.y/2 +70), sf::Vector2f(size.x - 40, size.y/14), font, sf::String("EXTENDED"));
    m_dropdownUp->addChoice("CHOICE I");
    m_dropdownUp->addChoice("CHOICE II");
    m_dropdownUp->addChoice("CHOICE III");
    m_dropdownUp->addChoice("CHOICE IV");

    m_dropdownDown->addChoice("CHOICE I");
    m_dropdownDown->addChoice("CHOICE II");
    m_dropdownDown->addChoice("CHOICE III");
    m_dropdownDown->addChoice("CHOICE IV");
}

PanelButton::~PanelButton()
{
    delete m_imageUp;
    delete m_imageDown;
    //delete tbutton;
    delete m_dropdownUp;
    delete m_dropdownDown;
}

void PanelButton::update(sf::Vector2i mousePos, sf::Event &event)
{   
    m_imageUp->update(mousePos, event);
    m_imageDown->update(mousePos, event);
    m_dropdownDown->update(mousePos, event);
    m_dropdownUp->update(mousePos, event);
}

void PanelButton::render(sf::RenderTarget *target) 
{   
    this->Panel::render(target);
    m_imageUp->render(target);
    m_imageDown->render(target);
    m_dropdownDown->render(target);
    m_dropdownUp->render(target);
}

ImageButton* PanelButton::getImageUp()
{
    return m_imageUp;
}

ImageButton* PanelButton::getImageDown()
{
    return m_imageDown;
}


