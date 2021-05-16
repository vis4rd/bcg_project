#pragma once
#include "Object.h"


class Button: public Object
{

    public:
    Button();

    



    private:
    unsigned short m_is_pressed;
    sf::Font* m_font;
    sf::Text m_text;



};