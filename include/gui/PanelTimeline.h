#pragma once

#include "Panel.h"
#include "StartStopControl.h"
#include "NextFrameControl.h"
#include "Timeline.h"


class PanelTimeline : public Panel
{

	public:
	PanelTimeline();
	PanelTimeline(const sf::Vector2f &pos, const sf::Vector2f &size);
	~PanelTimeline();

	void update(sf::Vector2i mousePos, sf::Event &event) override;
	void render(sf::RenderTarget *target) override;

	void play();
	void pause();
	void ON_OFF();
	bool isFinished(); 


	const float& getAnimTime();
	const NextFrameControl* getNext();
	const NextFrameControl* getPrev();
	const StartStopControl* getControl();
	const Timeline* getTimeline();

	/*
	*	void next(AnimatedImage* anim) i void previous(AnimatedImage* anim);
	*	- methods to set next animation and time that animation takes (m_animTime)
	*	  
	*/

	protected:
	StartStopControl* m_control;
	NextFrameControl* m_next;
	NextFrameControl* m_prev;
	Timeline* m_timeline;
	float m_animTime;

}; 