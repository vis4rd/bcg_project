#pragma once

#include "Panel.h"
#include "StartStopControl.h"
#include "NextFrameControl.h"
#include "Timeline.h"
#include "Canvas.h"


/**
 * @brief Class responsible for animation display and timeline serivce
 */
class PanelTimeline : public Panel
{
public:

	/**
	 * @brief Constructor setting position and size od panel
	 *
	 * @param pos The position
	 * @param size The size
	 */
	PanelTimeline(const sf::Vector2f &pos, const sf::Vector2f &size);
	
	/**
	 * @brief Destructor
	 */
	~PanelTimeline();

	/**
	 * @brief Return information if animation is finished
	 *
	 * @return True if finished, False otherwise.
	 */
	bool isFinished(); 

	/**
	 * @brief Getter to the next frame button
	 *
	 * @return The nextFrameButton.
	 */
	NextFrameControl* getNext();

	/**
	 * @brief Getter to the prev frame button
	 *
	 * @return The prevFrameButton.
	 */
	NextFrameControl* getPrev();

	/**
	 * @brief Gets the control.
	 *
	 * @return The control.
	 */
	StartStopControl* getControl();
	
	/**
	 * @brief Gets the timeline.
	 *
	 * @return The timeline.
	 */
	Timeline* getTimeline();
	
	/**
	 * @brief Gets the canvas.
	 *
	 * @return The canvas.
	 */
	Canvas* getCanvas();

	/**
	 * @brief updating state and look of 
	 *
	 * @param mousePos The mouse position
	 * @param event The event
	 * @param deltaTime The delta time
	 */
	void update(sf::Vector2i mousePos, sf::Event &event, const float &deltaTime);
	
	/**
	 * @brief Renders the given target.
	 *
	 * @param target The target
	 */
	void render(sf::RenderTarget *target) override;

protected:
	StartStopControl* m_control;
	NextFrameControl* m_next;
	NextFrameControl* m_prev;
	Canvas* m_canvas;
	Timeline* m_timeline;
}; 
