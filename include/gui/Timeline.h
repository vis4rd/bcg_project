#pragma once
#include "Button.h"

class Timeline: public Button
{
public:
    Timeline();
    Timeline(sf::Vector2f pos, sf::Vector2f size, const float totalTime, const unsigned framesPerSecond = 60);
    ~Timeline() = default;

    void play();
    void pause();

    void setPlayStatusON_OFF(const bool on = false);
    void setCursorPosition(float localY);
    void setTotalTime(const float totalTime);
    void setFrames(const unsigned frames);
    
    const float getCursorProgress() const; // <0, 1>
    const float getTotalTime() const;
    const float getCurrentTime() const;
    const bool isFinished() const;
    const bool getPlayStatus() const;
    const unsigned getFrames() const;

    void update(sf::Vector2i mousePos, sf::Event &event, const float &deltaTime);
    void render(sf::RenderTarget *target);

private:
    // void setCursorSpeed(); // redundant?
    void setCurrentTime(const float currentTime);

protected:
    sf::CircleShape m_cursor;
    sf::RectangleShape m_box;
    sf::RectangleShape m_covered;
    //sf::VertexArray *m_body; // redundant?

    float m_timelineLength;
    float m_cursorSpeed;
    bool m_playStatus;
    float m_totalTime;
    float m_currentTime;
    unsigned m_frameCount;
};
