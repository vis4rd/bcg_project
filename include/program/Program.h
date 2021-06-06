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
#include "../gui/AnimatedImage.h"
#include "../gui/Object.h"
#include "../gui/Canvas.h"

class Program
{
public:
	Program();
	~Program();

	void endApp();

	void updateDeltaTime();
	void updateSFMLEvents();
	void update(sf::Vector2i mousePos, sf::Event &event);

	void render();

	void run();

private:
	sf::RenderWindow *m_window;
	sf::Event m_event;

	sf::Clock m_dtClock;
	float m_deltaTime;

	PanelTimeline *m_timePanel;
	PanelButton *m_buttonPanel;
	Canvas *m_canvas;
};
