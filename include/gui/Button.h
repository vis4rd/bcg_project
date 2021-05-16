#pragma once
#include "Object.h"

//virtual class with interface for all buttons obcjets
class Button: public Object
{
    public:
    enum state
    {
    	IDLE = 0,
    	HOVER = 1,
    	ACTIVE = 2
    };

    //constructors and destructors
    Button();
    Button(const sf::Vector2f &pos, const sf::Vector2f &size);
    ~Button() =  default;

    //getters
    const unsigned short getState();

    //setters
    void setState(const unsigned short state);

    //check and update methods
    bool isPressed();
    void update(sf::Vector2i mousePos) override;
    void render(sf::RenderTarget *target) override;

    protected:
    unsigned short m_state;

};