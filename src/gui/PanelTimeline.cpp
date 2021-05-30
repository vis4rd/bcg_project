#include "../../include/gui/PanelTimeline.h"


PanelTimeline::PanelTimeline()
:
Panel()
{}

PanelTimeline::PanelTimeline(const sf::Vector2f &pos, const sf::Vector2f &size)
:
Panel(pos, size)
{
	float tempX = size.x/2.f;
	float tempY = size.y/14.f;
	m_control = new StartStopControl( pos + sf::Vector2f(tempX,tempY) );
	m_next = NextFrameControl::makeNextFrameButton( pos+sf::Vector2f(tempX+55.f, tempY + 3.f ) );
	m_prev = NextFrameControl::makePreviousFrameButton( pos+sf::Vector2f(tempX-55.f, tempY + 3.f ) );
	m_timeline = new Timeline( (pos+sf::Vector2f(size.x/16.f, tempY+65.f)) , sf::Vector2f( 14.f*size.x/16.f  , 1.f));
}

PanelTimeline::~PanelTimeline()
{
	delete m_timeline;
	delete m_next;
	delete m_prev;
	delete m_control;
}

void PanelTimeline::update(sf::Vector2i mousePos, sf::Event &event)
{
	m_control->update(mousePos, event);
    m_next->update(mousePos, event);
    m_prev->update(mousePos, event);
    m_timeline->update(mousePos, event);

    if( m_control->isPressed() )
    {
        m_timeline->ON_OFF();
    }
    m_timeline->isPlay() ? m_control->play() : m_control->pause(); 
}

void PanelTimeline::render(sf::RenderTarget *target)
{
	this->Panel::render(target);
	m_control->render(target);
   	m_next->render(target);
   	m_prev->render(target);
   	m_timeline->render(target);

   	if ( m_timeline->isFinished() )
   	{
    	m_control->pause();
   	}
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
	m_timeline->ON_OFF();
}

bool PanelTimeline::isFinished()
{
	return m_timeline->isFinished();
} 