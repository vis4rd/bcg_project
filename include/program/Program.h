#pragma once

#include "../gui/DropdownList.h"
#include "../gui/StartStopControl.h"
#include "../gui/NextFrameControl.h"
#include "../gui/Timeline.h"
#include "../gui/PanelTimeline.h"
#include "../gui/PanelButtons.h"

#include "../animation/PixelAnimation.h"
#include "../animation/ObjectAnimation.h"
#include "../animation/DimmingAnimation.h"
#include "../animation/AlfaAnimation.h"
#include "../animation/ByBrightnessAnimation.h"
#include "../animation/SlideAnimation.h"
#include "../animation/ScaleAnimation.h"
#include "../animation/RingAnimation.h"
#include "../animation/FlyAnimation.h"

#include "../gui/AnimatedImage.h"
#include "../gui/Object.h"
#include "../gui/Canvas.h"
#include "../gui/Settings.h"

/**
 * @brief Class merging everything from the application into one place
 */
class Program
{
public:
	/**
	 * Constructor starting the application
	 */
	Program();

	/**
	 * @brief Destructor cleaning up after application's termination
	 */
	~Program();

	/**
	 * @brief This method is called at application's end
	 */
	void endApp();

	/**
	 * @brief Sets the animation type from application's settings
	 *
	 * @param settings The pointer to Setting's instance
	 */
	void setAnimationFromSettings(Settings* settings);

	/**
	 * @brief Sets the frame count of the animation from application's settings
	 *
	 * @param settings The pointer to Setting's instance
	 */
	void setFramesFromSettings(Settings* settings);
	
	/**
	 * @brief This member function sets a flag calling Program's update even if there's no event happening at the moment
	 */
	static void requestUpdate();

	/**
	 * @brief This member function expires the request for calling Program's update
	 */
	static void expireRequestUpdate();


	/**
	 * @brief Update of delta time
	 * 
	 * Delta time is a time measured from drawing previous frame to generating the next one.
	 * The faster is the computer (more frames per second) the smaller is the delta time.
	 */
	void updateDeltaTime();

	/**
	 * @brief Update all events happening in the application
	 */
	void updateSFMLEvents();

	/**
	 * @brief Gather up all main updates of the application
	 *
	 * @param mousePos The mouse position relative to the window
	 * @param event The event handler 
	 */
	void update(sf::Vector2i mousePos, sf::Event &event);

	/**
	 * @brief Save a sequence of bitmaps from animation into the file on hard drive
	 *
	 * @param mousePos The mouse position given to updates of Canvas and Timeline
	 * @param event The event handler given to updates of Canvas and Timeline
	 */
	void saveSequence(sf::Vector2i mousePos, sf::Event &event);

	/**
	 * @brief Renders everything into the window
	 */
	void render();

	/**
	 * @brief Run method is called by main function
	 */
	void run();

private:
	std::unique_ptr<sf::RenderWindow> m_window;///> Target which all object are rendered to
	sf::Event m_event;///> Event handler

	sf::Clock m_dtClock;///> Clock measuring delta time between frames
	float m_deltaTime;///> Time between rendered frames

	std::unique_ptr<PanelTimeline> m_timePanel;///> Panel containing applications contents
	std::unique_ptr<PanelButton> m_buttonPanel;///> Panel containing applications settings

	static bool requestedUpdate;///> Flag declaring whether window should be updated without event or not
};
