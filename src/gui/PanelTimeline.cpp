#include "../../include/gui/PanelTimeline.h"

PanelTimeline::PanelTimeline()
:
Panel(),
m_control(nullptr),
m_next(nullptr),
m_prev(nullptr),
m_canvas(nullptr),
m_timeline(nullptr)
{
	m_canvas = new Canvas();
}

PanelTimeline::PanelTimeline(const sf::Vector2f &pos, const sf::Vector2f &size)
:
Panel( sf::Vector2f( pos.x, pos.y + size.y*(9.f/10.f) ), sf::Vector2f( size.x, size.y/8.f) )
{
	float tempY = pos.y + size.y*(9.f/10.f);
	m_timeline = new Timeline( (pos+sf::Vector2f(size.x/16.f, tempY+55.f)) , sf::Vector2f( 14.f*size.x/16.f  , 1.f) );
	
	m_control = new StartStopControl( pos + sf::Vector2f( size.x/16.f + 14.f*size.x/32.f - 20.f, tempY) );
	m_next = NextFrameControl::makeNextFrameButton( pos+sf::Vector2f( size.x/16.f + 14.f*size.x/32.f + 30.f, tempY+3) );
	m_prev = NextFrameControl::makePreviousFrameButton( pos+sf::Vector2f( size.x/16.f + 14.f*size.x/32.f - 70.f, tempY+3) );
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

void PanelTimeline::update(sf::Vector2i mousePos, sf::Event &event, const float &deltaTime)
{
	m_control->update(mousePos, event);

    m_timeline->setPlayStatusON_OFF(m_control->isPlay());
    m_canvas->setAnimationPlayOn(m_control->isPlay());

    m_next->update(mousePos, event);
    if( m_next->isPressed() )
    {
    	m_timeline->skipNextFrame();
    	m_control->pause();
    }

    m_prev->update(mousePos, event);
    if( m_prev->isPressed() )
    {
    	m_timeline->skipPrevFrame();
    	m_control->pause();
    }
    
    m_timeline->update(mousePos, event, deltaTime);
    if(m_control->isPlay() && !m_timeline->getPlayStatus())//it is necessary in case user clicked on the timeline
    {
    	m_control->pause();
    }

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
