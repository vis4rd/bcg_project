#include "../../include/gui/PanelTimeline.h"

PanelTimeline::PanelTimeline(const sf::Vector2f &pos, const sf::Vector2f &size)
:
Panel( sf::Vector2f( pos.x, pos.y ), sf::Vector2f( size.x, size.y) )
{
	m_canvas = std::make_shared<Canvas>(	pos + sf::Vector2f(6.f, 6.f),
					sf::Vector2f(size.x - 12.f, size.y * (17.f/20.f)));

	m_control = std::make_shared<StartStopControl>(sf::Vector2f(
					pos.x + 6.f + ((size.x - 12.f) / 2.f) - 20.f,
					pos.y + 6.f + (size.y * (17.f/20.f)) + 15.f));
	
	m_next = std::shared_ptr<NextFrameControl>(NextFrameControl::makeNextFrameButton(sf::Vector2f(
					m_control->getPosition().x + m_control->getSize().x + 20.f,
					m_control->getPosition().y) ));
	m_prev = std::shared_ptr<NextFrameControl>(NextFrameControl::makePreviousFrameButton( sf::Vector2f(
					m_control->getPosition().x - m_control->getSize().x - 20.f,
					m_control->getPosition().y) ));

	m_timeline = std::make_shared<Timeline>(
		sf::Vector2f(pos.x + (size.x / 2.f) - (size.x * (9.f/10.f) / 2.f),
					m_control->getPosition().y + m_control->getSize().y + 15.f),
		sf::Vector2f(size.x * (9.f/10.f), 5.f));
}

bool PanelTimeline::isFinished()
{
	return m_timeline->isFinished();
} 

std::shared_ptr<NextFrameControl> PanelTimeline::getNext()
{
	return m_next;
}

std::shared_ptr<NextFrameControl> PanelTimeline::getPrev()
{
	return m_prev;
}

std::shared_ptr<StartStopControl> PanelTimeline::getControl()
{
	return m_control;
}

std::shared_ptr<Timeline> PanelTimeline::getTimeline()
{
	return m_timeline;
}

std::shared_ptr<Canvas> PanelTimeline::getCanvas()
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
    if(m_control->isPlay() && (!m_timeline->getPlayStatus() || m_timeline->isFinished()))
    //it is necessary in case user clicked on the timeline
    {
    	m_control->pause();
    }

    m_canvas->setCurrentAnimationTime(m_timeline->getCurrentTime());
	m_canvas->update(mousePos, event);
}

void PanelTimeline::render(std::shared_ptr<sf::RenderTarget> target)
{
	Panel::render(target);
	m_control->render(target);
   	m_next->render(target);
   	m_prev->render(target);
   	m_timeline->render(target);
   	m_canvas->render(target);
}
