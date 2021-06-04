#include "../../include/gui/StartStopControl.h"

StartStopControl::StartStopControl()
:
AnimControlButton()
{
	m_texture.loadFromFile("../res/images/play_button.png");
} 


StartStopControl::StartStopControl(const sf::Vector2f &pos)
:
AnimControlButton(pos)
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
	if ( this->isAnimationActive() )
	{
		if ( m_shape.getGlobalBounds().contains(mousePos.x, mousePos.y) )
		{
			m_state = Button::state::HOVER;
			m_sprite.setColor( sf::Color(180,180,180) );

			if( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
			{
				if ( this->isPlay() )
				{
					m_state = Button::state::ACTIVE;
					m_sprite.setColor( sf::Color(250,250,250)  );
					this->pause();
				}
				else
				{
					m_state = Button::state::ACTIVE;
					m_sprite.setColor( sf::Color(250,250,250)  );
					this->play();
				}
			}

		}

		else
		{
			m_state = Button::state::IDLE;
			m_sprite.setColor( sf::Color(150,150,150) );
		}
	}
	else
	{
		if ( m_shape.getGlobalBounds().contains(mousePos.x, mousePos.y) )
		{
			m_state = Button::state::HOVER;
			m_sprite.setColor( sf::Color(240,240,100) );

			if( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
			{
				m_sprite.setColor( sf::Color(100,100,100) );	
			}
		}
		
		else
		{
			m_state = Button::state::IDLE;
			m_sprite.setColor( sf::Color(150,150,150) );
		}

	}
}


void StartStopControl::render(sf::RenderTarget *target) 
{
	AnimControlButton::render(target);
}

void StartStopControl::ON_OFF()
{
	m_isPlay = !m_isPlay;
}
