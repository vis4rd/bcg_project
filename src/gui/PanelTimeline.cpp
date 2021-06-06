#include "../../include/gui/PanelTimeline.h"


PanelTimeline::PanelTimeline()
:
Panel()
{
	m_canvas = new Canvas();
}

PanelTimeline::PanelTimeline(const sf::Vector2f &pos, const sf::Vector2f &size)
:
Panel( sf::Vector2f( pos.x, pos.y + size.y*(9.f/10.f) ), sf::Vector2f( size.x, size.y/8.f) )
{
	float tempX = pos.y + size.x/(2.f);
	float tempY = pos.y + size.y*(9.f/10.f);
	m_control = new StartStopControl( pos + sf::Vector2f(tempX,tempY) );
	m_next = NextFrameControl::makeNextFrameButton( pos+sf::Vector2f(tempX+55.f, tempY + 3.f ) );
	m_prev = NextFrameControl::makePreviousFrameButton( pos+sf::Vector2f(tempX-55.f, tempY + 3.f ) );
	m_timeline = new Timeline( (pos+sf::Vector2f(size.x/16.f, tempY+65.f)) , sf::Vector2f( 14.f*size.x/16.f  , 1.f), 5.f);
	m_canvas = new Canvas(pos , sf::Vector2f(size.x, size.y * (7.f/8.f)) );
}

PanelTimeline::~PanelTimeline()
{
	delete m_timeline;
	delete m_next;
	delete m_prev;
	delete m_control;
	delete m_canvas;
}

void PanelTimeline::update(sf::Vector2i mousePos, sf::Event &event, const float &deltaTime)
{
	m_control->update(mousePos, event);
    m_next->update(mousePos, event);
    m_prev->update(mousePos, event);
    m_timeline->update(mousePos, event, deltaTime);

    if(m_control->isPressed()) //if start pressed, play/pause the timeline cursor
    {
    	/*m_timeline->setTotalTime( m_canvas->getTotalTime() );*/
        m_timeline->setPlayStatusON_OFF();
        
    }

    // ---------------IMPORTANT!-------------------
    if( !m_timeline->getPlayStatus() ) //this condition should not be necessary, but somehow its required for start button proper behaviour
   	{	//some mistake in ON_OFF() of m_control?
    	m_control->pause();
   	}

    /*if(m_timeline->getPlayStatus())
    {
	    m_canvas->setCurrentAnimationProgress( m_timeline->getCursorProgress() );
	}*/
	//Timeline decides whether the time should be the same (paused) or progressed (played)
	m_canvas->setAnimationPlayOn(m_control->isPlay());
	m_canvas->setCurrentAnimationTime(m_timeline->getCurrentTime());
	m_canvas->update(mousePos, event);
}

void PanelTimeline::render(sf::RenderTarget *target)
{
	this->Panel::render(target);
	m_control->render(target);
   	m_next->render(target);
   	m_prev->render(target);
   	m_timeline->render(target);
   	m_canvas->render(target);
}

void PanelTimeline::play()
{
	m_control->play();
	m_timeline->play();

}

void PanelTimeline::pause()
{
	m_control->pause();
	m_timeline->pause();
}

void PanelTimeline::ON_OFF()
{
	m_control->ON_OFF();
	m_timeline->setPlayStatusON_OFF();
}

bool PanelTimeline::isFinished()
{
	return m_timeline->isFinished();
} 

NextFrameControl* PanelTimeline::getNext()
{
	return m_next;
}

NextFrameControl* PanelTimeline::getPrev()
{
	return m_prev;
}

StartStopControl* PanelTimeline::getControl()
{
	return m_control;
}

Timeline* PanelTimeline::getTimeline()
{
	return m_timeline;
}

Canvas* PanelTimeline::getCanvas()
{
	return m_canvas;
}
