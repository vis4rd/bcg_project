#include "../../include/gui/StartStopControl.h"

StartStopControl::StartStopControl()
:
AnimControlButton(),
m_isPlay(false)
{
	m_texture.loadFromFile("../res/images/play_button.png");
} 


StartStopControl::StartStopControl(const sf::Vector2f &pos)
:
AnimControlButton(pos),
m_isPlay(false)
{
	m_texture.loadFromFile("../res/images/play_button.png");
	m_sprite.setTexture(m_texture);
} 


bool StartStopControl::isPlay() const
{
	return m_isPlay;
}


void StartStopControl::play()
{
	m_isPlay = true;
	m_texture.loadFromFile("../res/images/pause_button.png");
	m_sprite.setTexture(m_texture);
}


void StartStopControl::pause()
{
	m_isPlay = false;
	m_texture.loadFromFile("../res/images/play_button.png");
	m_sprite.setTexture(m_texture);
}


void StartStopControl::update(sf::Vector2i mousePos, sf::Event &event) 
{
	if(m_shape.getGlobalBounds().contains(mousePos.x, mousePos.y))
	{
		m_state = Button::state::HOVER;
		if((event.type == sf::Event::MouseButtonReleased)
		&& (event.mouseButton.button == sf::Mouse::Left))
		{
			m_state = Button::state::ACTIVE;
			this->ON_OFF();
		}
	}
	else
	{
		m_state = Button::state::IDLE;
	}

	switch(m_state)
	{
		case Button::state::IDLE: m_sprite.setColor(sf::Color(150,150,150)); break;
		case Button::state::HOVER: m_sprite.setColor(sf::Color(180,180,180)); break;
		case Button::state::ACTIVE: m_sprite.setColor(sf::Color(250,250,250)); break;
		default: m_sprite.setColor(sf::Color(255,255,255));
	}
}


void StartStopControl::render(sf::RenderTarget *target) 
{
	AnimControlButton::render(target);
}

void StartStopControl::ON_OFF()
{
	m_isPlay = !m_isPlay;
	if(m_isPlay)
	{
		m_texture.loadFromFile("../res/images/pause_button.png");
	}
	else
	{
		m_texture.loadFromFile("../res/images/play_button.png");
	}
}
