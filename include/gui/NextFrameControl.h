#pragma once 

#include "AnimControlButton.h"

/**
 * @brief      Class creating two buttons -of nextFrame and of PreviousFrame.
 */
class NextFrameControl : public AnimControlButton
{

public:
    /**
     * @brief      Dectructor
     */
	~NextFrameControl() = default;

	/**
	 * @brief      Static method creating the next frame button.
	 *
	 * @param  	   pos   The position
	 *
	 * @return     Button with proper texture of arrow directed right
	 */
	static NextFrameControl* makeNextFrameButton(const sf::Vector2f &pos);

	/**
	 * @brief      Static method creating the previous frame button.
	 *
	 * @param      pos   The position
	 *
	 * @return     Button with proper texture of arrow directed left
	 */
	static NextFrameControl* makePreviousFrameButton(const sf::Vector2f &pos);

	/**
	 * @brief      Renders button in target
	 *
	 * @param      target  The target
	 */
	void render(sf::RenderTarget *target) override;

	/**
	 * @brief      Updates state and look of button 
	 *
	 * @param      mousePos  The mouse position
	 * @param      event     The event
	 */
	void update(sf::Vector2i mousePos, sf::Event &event) override;

private:
	/**
	 * @brief      Private constructor
	 *
	 * @param      pos   The position
	 */
	NextFrameControl(const sf::Vector2f &pos);

};