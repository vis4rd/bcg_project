#pragma once
#include "Button.h"


/**
 * @brief      This class of timeline bar.
 */
class Timeline: public Button
{
public:
    /**
     * Default constructor
     */
    Timeline();

    /**
     * @brief      { function_description }
     *
     * @param      pos              The position
     * @param      size             The size
     * @param      totalTime        The total time
     * @param      frame            The frames 
     */
    Timeline(sf::Vector2f pos, sf::Vector2f size, const float totalTime = 1.f, const unsigned short frames = 60);

    /**
     * @brief      Destructor
     */
    ~Timeline() = default;

    /**
     * @brief      Set status on play
     */
    void play();

    /**
     * @brief      Set status on pause
     */
    void pause();

    /**
     * @brief      Switch between play and pause.
     *
     * @param      on - if on value true/flase (false defaulty)
     */
    void setPlayStatusON_OFF(const bool on = false);
    
    /**
     * @brief      Sets the cursor position.
     *
     * @param      localX  The new location
     */
    void setCursorPosition(float localX);
    
    /**
     * @brief      Sets the total time.
     *
     * @param      totalTime  The total time of animation
     */
    void setTotalTime(const float totalTime);
    
    /**
     * @brief      Sets the amount of frames.
     *
     * @param      frames  The frames amount
     */
    void setFrames(const unsigned short frames);
    
    /**
     * @brief      Sets the current time.
     *
     * @param      currentTime  The current time
     */
    void setCurrentTime(const float currentTime);
    
    /**
     * @brief      Jump to time of next frame
     */
    void skipNextFrame();
    
    /**
     * @brief      Jump to time of previous frame
     */
    void skipPrevFrame();
    
    /**
     * @brief      Getter to the cursor progress.
     *
     * @return     The cursor progress - value ranges from <0;1>.
     */
    const float getCursorProgress() const; 
    
    /**
     * @brief      Getter to the total time.
     *
     * @return     The total time of animation.
     */
    const float getTotalTime() const;
    
    /**
     * @brief      Getter to the current time.
     *
     * @return     The current animation time.
     */
    const float getCurrentTime() const;
    
    /**
     * @brief      Getter to the delta time between frames.
     *
     * @return     The time between frames.
     */
    const float getDeltaFrame() const;
    
    /**
     * @brief      Returns information if timeline achived end of range.
     *
     * @return     True if finished, False otherwise.
     */
    const bool isFinished() const;
    
    /**
     * @brief      Getter to the play status.
     *
     * @return     The play status true/false.
     */
    const bool getPlayStatus() const;
    
    /**
     * @brief      Getter to the frames counts.
     *
     * @return     The frames counts.
     */
    const unsigned getFrames() const;

    /**
     * @brief      Update state and look of timeline
     *
     * @param      mousePos   The mouse position
     * @param      event      The event
     * @param      deltaTime  The delta time
     * 
     * Checking if finshed - if true -> pause  
     * Updateing time
     * Updateing cursor position set with mouse  
     * Updateing covered patr of timeline (after cursor).  
     * 
     */
    void update(sf::Vector2i mousePos, sf::Event &event, const float &deltaTime);
    
    /**
     * @brief      Renders timeline on target.
     *
     * @param      target  The target
     */
    void render(sf::RenderTarget *target);


protected:
    sf::CircleShape m_cursor;
    sf::RectangleShape m_box;
    sf::RectangleShape m_covered;

    float m_timelineLength;
    float m_cursorSpeed;
    bool m_playStatus;
    float m_totalTime;
    float m_currentTime;
    float m_deltaFrame;
    unsigned short m_frameCount;
};
