#pragma once

#include "Panel.h"
#include "StartStopControl.h"
#include "NextFrameControl.h"
#include "Timeline.h"
#include "Canvas.h"



class PanelTimeline : public Panel
{

	public:
	PanelTimeline();
	PanelTimeline(const sf::Vector2f &pos, const sf::Vector2f &size);
	~PanelTimeline();

	void update(sf::Vector2i mousePos, sf::Event &event, const float &deltaTime);
	void render(sf::RenderTarget *target) override;

	void play();
	void pause();
	void ON_OFF();
	bool isFinished(); 


	NextFrameControl* getNext();
	NextFrameControl* getPrev();
	StartStopControl* getControl();
	Timeline* getTimeline();
	Canvas* getCanvas();


	protected:
	StartStopControl* m_control;
	NextFrameControl* m_next;
	NextFrameControl* m_prev;
	Canvas* m_canvas;
	Timeline* m_timeline;
}; 
