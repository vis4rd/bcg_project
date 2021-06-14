#pragma once
#include "Object.h"

/**
 * @brief      This class describes base(empty) panel.
 */
class Panel : public Object
{

	public:
	/**
	 * @brief      The constructor that sets position and size of panel 
	 *
	 * @param  	   pos   The position
	 * @param  	   size  The size
	 */
	Panel(const sf::Vector2f &pos , const sf::Vector2f &size);
	/**
	 * @brief      Dectructor
	 */
	~Panel() = default;

	/**
	 * @brief      Updates look of panel
	 *
	 * @param      mousePos  The mouse position
	 * @param      event     The event
	 */
	void update(sf::Vector2i mousePos, sf::Event &event) override;
	
	/**
	 * @brief      Renders panel in given target.
	 *
	 * @param      target  The target
	 */
	void render(sf::RenderTarget *target) override;

};
