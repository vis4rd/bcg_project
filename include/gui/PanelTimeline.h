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
	~PanelTimeline() = default;

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
	std::shared_ptr<NextFrameControl> getNext();

	/**
	 * @brief Getter to the prev frame button
	 *
	 * @return The prevFrameButton.
	 */
	std::shared_ptr<NextFrameControl> getPrev();

	/**
	 * @brief Getter to the control Button.
	 *
	 * @return The control Button.
	 */
	std::shared_ptr<StartStopControl> getControl();
	
	/**
	 * @brief Getter to the timeline.
	 *
	 * @return The timeline.
	 */
	std::shared_ptr<Timeline> getTimeline();
	
	/**
	 * @brief Getter to the canvas.
	 *
	 * @return The canvas.
	 */
	std::shared_ptr<Canvas> getCanvas();

	/**
	 * @brief updating state and look of whole panel 
	 *
	 * @param mousePos The mouse position
	 * @param event The event
	 * @param deltaTime The delta time
	 * 
	 * 
	 * Serivcing of logic of buttons, timeline and animations:
	 * - jumping between frames, 
	 * - play/pause switching,
	 * - updating time and animation,
	 * - updating animation depending of set of timeline cursor 
	 * 
	 */
	void update(sf::Vector2i mousePos, sf::Event &event, const float &deltaTime);
	
	/**
	 * @brief Renders the given target.
	 *
	 * @param target The target
	 */
	void render(std::shared_ptr<sf::RenderTarget> target) override;

protected:
	std::shared_ptr<StartStopControl> m_control;
	std::shared_ptr<NextFrameControl> m_next;
	std::shared_ptr<NextFrameControl> m_prev;
	std::shared_ptr<Canvas> m_canvas;
	std::shared_ptr<Timeline> m_timeline;
}; 
