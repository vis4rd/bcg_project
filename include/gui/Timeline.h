#pragma once
#include "Button.h"

class Timeline: public Button
{
public:
    Timeline();
    Timeline(sf::Vector2f pos, sf::Vector2f size);
    ~Timeline() = default;

    bool isPlay() const;

    void ON_OFF();
    void play();
    void pause();

    bool isFinished() ;

    void render(sf::RenderTarget *target);
    void setCursorPosition(float localY);
    void update(sf::Vector2i mousePos, sf::Event &event);

protected:
    sf::CircleShape m_cursor;
    sf::RectangleShape m_box;
    sf::RectangleShape m_covered;
    sf::VertexArray *m_body;
    double m_length;
    bool m_ONOFF = false;
};
