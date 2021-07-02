#pragma once

#include "AnimControlButton.h"

/**
 * @brief      The class describes button for starting and stoping animation
 */
class StartStopControl : public AnimControlButton
{
public:
    /**
     * Default constructor
     */
	StartStopControl(); 

    /**
     * @brief      Costructor with position setting
     *
     * @param      pos   The position
     */
	StartStopControl(const sf::Vector2f &pos);

    /**
     * @brief      Destructor
     */
	~StartStopControl() = default;

	/**
     * @brief      Updates state and look of button
     *
     * @param      mousePos  The mouse position
     * @param      event     The event
     */
	void update(sf::Vector2i mousePos, sf::Event &event) override;
    
    /**
     * @brief      Renders button in given target
     *
     * @param      target  The target
     * 
     * Changing texture of button depending to play/pause 
     * 
     */
    void render(std::shared_ptr<sf::RenderTarget> target) override;

    /**
     * @brief      Gets information if button is on play.
     *
     * @return     True if play, False otherwise.
     */
    bool isPlay() const;

    /**
     * @brief      Sets button on play
     */
    void play();
    
    /**
     * @brief      Sets button on pasue
     */
    void pause();
    
    /**
     * @brief      Switching button state of button between play and pause.
     */
    void ON_OFF();

private:
	bool m_isPlay;
};
