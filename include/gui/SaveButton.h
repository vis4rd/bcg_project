#pragma once

#include "Button.h"


/**
 * @brief      This class of button with save icon.
 */
class SaveButton : public Button
{
public:

	/**
	 * @brief       Constructor that sets position and size of button.
	 *
	 * @param       pos   The position
	 * @param       size  The size
	 */
	SaveButton(const sf::Vector2f &pos, const sf::Vector2f &size);
	
	/**
	 * @brief      Copy constructor
	 *
	 * @param      copy  orginal instatntion of SaveButton 
	 */
	SaveButton(const SaveButton &copy);
	
	/**
	 * @brief      Move constructor.
	 *
	 * @param      source  orginal instatntion of SaveButton
	 */
	SaveButton(SaveButton &&source);

	/**
	 * @brief      Renders button in given target.
	 *
	 * @param      target  The target
	 */
	void render(sf::RenderTarget *target) override;
	
	/**
     * @brief      Updates state and look of button. 
     *
     * @param      mousePos  The mouse position
     * @param      event     The event
     */
	void update(sf::Vector2i mousePos, sf::Event &event) override;

private:
	sf::Sprite m_spr;
	sf::Texture m_texture;
};	