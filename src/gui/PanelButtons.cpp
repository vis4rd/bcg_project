#include "../../include/gui/PanelButtons.h"


PanelButton::PanelButton(const sf::Vector2f &pos, const sf::Vector2f &size)
:
Panel(pos,size)
{
    m_imageUp = new ImageButton(sf::Vector2f(pos.x + 10,pos.y + 10 ), sf::Vector2f(size.x - 20,size.y/4));
    m_imageDown = new ImageButton(sf::Vector2f(pos.x + 10 , pos.y + 30 + size.y/4.f), sf::Vector2f(size.x - 20,size.y/4));
    m_saveButton = new SaveButton(sf::Vector2f(pos.x + size.x/2 -50.f, pos.y + size.y - 55.f ), sf::Vector2f(100.f, 50.f) );

    font = std::make_shared<sf::Font>();
    
    m_animationChoice = new DropdownList(sf::Vector2f(pos.x + 20, pos.y + 50 + size.y/2), sf::Vector2f(size.x - 40, size.y/14), font, sf::String("Dimming"));
    m_animationChoice->addChoice("Dimming");
    m_animationChoice->addChoice("Fading");
    m_animationChoice->addChoice("Pixels Brightness");
    m_animationChoice->addChoice("Slide Left to Right");//or Swipe Right
    m_animationChoice->addChoice("Scale From Point");
    m_animationChoice->addChoice("Ring Animation");
    m_animationChoice->addChoice("Fly Away Animation");
    
    m_framesChoice = new DropdownList(sf::Vector2f(pos.x + 20, pos.y + size.y/14 + size.y/2 +70), sf::Vector2f(size.x - 40, size.y/14), font, sf::String("15 frames"));
    m_framesChoice->addChoice("15 frames");
    m_framesChoice->addChoice("30 frames");
    m_framesChoice->addChoice("60 frames");
    m_framesChoice->addChoice("120 frames");
    m_framesChoice->addChoice("Your Choice");
}

PanelButton::~PanelButton()
{
    delete m_imageUp;
    delete m_imageDown;
    delete m_animationChoice;
    delete m_framesChoice;
    delete m_saveButton;
}

void PanelButton::update(sf::Vector2i mousePos, sf::Event &event)
{   
    m_imageUp->update(mousePos, event);
    m_imageDown->update(mousePos, event);
    m_framesChoice->update(mousePos, event);
    if(m_framesChoice->isDropped())
    {
        m_animationChoice->lockButton();
        m_saveButton->lockButton();
    }
    
    if(m_animationChoice->getState() == Button::state::LOCKED
        && !m_framesChoice->isDropped()
        && !m_framesChoice->isChanged())
    {
        m_animationChoice->unlockButton();
        m_saveButton->unlockButton();
    }

    m_animationChoice->update(mousePos, event);
    if(m_animationChoice->isDropped())
    {
        m_framesChoice->lockButton();
        m_saveButton->lockButton();
    }
    
    if(m_framesChoice->getState() == Button::state::LOCKED
        && !m_animationChoice->isDropped()
        && !m_animationChoice->isChanged())
    {
        m_framesChoice->unlockButton();
        m_saveButton->unlockButton();
    }
    m_saveButton->update(mousePos, event);
}

void PanelButton::render(sf::RenderTarget *target) 
{   
    this->Panel::render(target);
    m_imageUp->render(target);
    m_imageDown->render(target);
    m_saveButton->render(target);
    m_framesChoice->render(target);
    m_animationChoice->render(target);
}

ImageButton* PanelButton::getImageUp()
{
    return m_imageUp;
}

ImageButton* PanelButton::getImageDown()
{
    return m_imageDown;
}

SaveButton* PanelButton::getSaveButton()
{
    return m_saveButton;
}

DropdownList* PanelButton::getAnimationChoice()
{
    return m_animationChoice;
}

DropdownList* PanelButton::getFramesChoice()
{
    return m_framesChoice;
}

const bool PanelButton::isChanged() const
{
    //return m_imageDown->isChanged() || m_imageUp->isChanged() || m_animationChoice->isChanged();
    return m_imageDown->isChanged() || m_imageUp->isChanged() 
            || m_animationChoice->isChanged() || m_framesChoice->isChanged();
}

void PanelButton::changesRead()
{
    m_imageUp -> changeRead();
    m_imageDown -> changeRead();
    m_animationChoice -> changeRead();
    m_framesChoice -> changeRead();
}
