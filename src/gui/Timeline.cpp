#include "../../include/gui/Timeline.h"

Timeline::Timeline()
:
Button(),
m_cursor(),
m_box(),
m_covered(),
m_timelineLength(0.f),
m_cursorSpeed(0.f),
m_playStatus(false),
m_totalTime(0.f),
m_currentTime(0.f),
m_frameCount(0u)
{
    m_shape.setOutlineThickness(1);
    m_shape.setOutlineColor(sf::Color::White);
}

Timeline::Timeline(sf::Vector2f pos, sf::Vector2f size, const float totalTime, const unsigned short framesPerSecond)
:
Button(pos,size),
m_timelineLength(size.x - 10.f),
m_playStatus(false),
m_totalTime(totalTime),
m_currentTime(0.f)
{
    m_cursor = sf::CircleShape(size.y + 1.f);
    m_cursor.setFillColor(sf::Color::White);
    m_cursor.setPosition(pos - sf::Vector2f(0.f, m_cursor.getRadius() / 2.f)); 
    m_cursor.setOutlineThickness(0.f);

    m_box.setPosition(pos);
    m_box.setSize(size);
    m_box.setFillColor( sf::Color(120,120,120) );
    m_box.setOutlineColor(sf::Color::Transparent);

    m_covered.setPosition(pos);
    m_covered.setFillColor(sf::Color(60,220,60));
    m_covered.setSize(sf::Vector2f(m_cursor.getPosition().x - m_covered.getPosition().x, size.y));

    m_playStatus = false;
    m_frameCount = framesPerSecond * m_totalTime;
    m_deltaFrame = m_totalTime/static_cast<float>(m_frameCount);
}

const bool Timeline::getPlayStatus() const
{
    return m_playStatus;
}

void Timeline::play()
{
    m_playStatus = true;
}

void Timeline::pause()
{
    m_playStatus = false;
}

void Timeline::setCursorPosition(float localX)
{
    m_cursor.setPosition(this->getPosition() + sf::Vector2f(localX, -m_cursor.getRadius() / 2.f) );
    m_covered.setSize(sf::Vector2f(m_cursor.getPosition().x - m_covered.getPosition().x, this->getSize().y));
}

void Timeline::setPlayStatusON_OFF(const bool on)
{
    m_playStatus = on;
}

const bool Timeline::isFinished() const
{
    if ( m_currentTime >= m_totalTime - 0.0002f) //-0.0002f is a correction because of IEEE754
    {
        return true;
    }
    else
    {
        return false;   
    }
}

void Timeline::setTotalTime(const float totalTime)
{
    if (totalTime > 0.f)
    {
        m_totalTime = totalTime;
        m_deltaFrame = m_totalTime/static_cast<float>(m_frameCount);
    }
} 

void Timeline::setFrames(const unsigned short frames)
{
    m_frameCount = frames;
    m_deltaFrame = m_totalTime/static_cast<float>(m_frameCount);
}

void Timeline::setCurrentTime(const float currentTime)
{
    if(currentTime >= 0.f && currentTime < m_totalTime)
    {
        m_currentTime = currentTime;
    }
}

const float Timeline::getCursorProgress() const
{
    return (m_cursor.getPosition().x - this->getPosition().x) / (m_timelineLength);  
}

const float Timeline::getTotalTime() const
{
    return m_totalTime;
}

const float Timeline::getCurrentTime() const
{
    return m_currentTime;
}

const unsigned Timeline::getFrames() const
{
    return m_frameCount;
}

void Timeline::skipNextFrame()
{
    float toJump = 0.f;
    while( toJump <= m_currentTime )
    {
        toJump += m_deltaFrame;
    }
    toJump >= m_totalTime ? toJump = m_totalTime - 0.0001 : 1 ;

    this->setCurrentTime( toJump );
    this->setCursorPosition(m_currentTime/m_totalTime * (m_timelineLength));
}


void Timeline::skipPrevFrame()
{
    float toJump = m_totalTime;
    while( toJump >= m_currentTime )
    {
        toJump -= m_deltaFrame;
    }
    toJump <= 0.f ? toJump = 0.f : 1 ;

    this->setCurrentTime( toJump );
    this->setCursorPosition(m_currentTime/m_totalTime * (m_timelineLength));
}

void Timeline::update(sf::Vector2i mousePos, sf::Event &event, const float &deltaTime)
{   
    if(this->isFinished())
    {
        this->pause();
    }
    else if(m_playStatus && !this->isFinished()) //animation is being played
    {
        m_currentTime += deltaTime;
        if(m_currentTime > m_totalTime)
        {
            m_currentTime = m_totalTime - 0.0001f;
        }
    }
    //adjust cursor's position
    this->setCursorPosition(m_currentTime/m_totalTime * (m_timelineLength));
    //color the path behind the cursor
    m_covered.setSize(sf::Vector2f(m_cursor.getPosition().x - m_covered.getPosition().x, this->getSize().y));

    if(m_box.getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y)))
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->pause();
            this->setCursorPosition(mousePos.x - m_box.getPosition().x);
            this->setCurrentTime((m_cursor.getPosition() - this->getPosition()).x / m_timelineLength * m_totalTime);
        }
    }
}

void Timeline::render(sf::RenderTarget *target) 
{
    target->draw(this->m_box);
    target->draw(this->m_covered);
    target->draw(this->m_cursor);
}
