#pragma once
#include "Object.h"

//virtual class with interface for all buttons obcjets
class Button: public Object
{
public:
    enum state
    {
        LOCKED = 0,
    	IDLE = 1,
    	HOVER = 2,
    	ACTIVE = 3
    };

    //constructors and destructors
    Button();
    Button(const sf::Vector2f &pos, const sf::Vector2f &size);
    ~Button() =  default;

    //getters
    const unsigned short getState() const;

    //setters
    void setState(const unsigned short new_state);

    //check and update methods
    bool isPressed() const;
    void lockButton();
    void unlockButton();
    void update(sf::Vector2i mousePos, sf::Event &event) override;
    void render(sf::RenderTarget *target) override;

protected:
    unsigned short m_state;

};
