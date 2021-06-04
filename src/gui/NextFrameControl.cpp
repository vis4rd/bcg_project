#include "../../include/gui/NextFrameControl.h"



NextFrameControl::NextFrameControl()
:
AnimControlButton()
{
	m_texture.loadFromFile("../res/images/empty_button.png");
} 



NextFrameControl::NextFrameControl(const sf::Vector2f &pos)
:
AnimControlButton(pos)
{}

NextFrameControl* NextFrameControl::makeNextFrameButton(const sf::Vector2f &pos)
{
	NextFrameControl* outObj = new NextFrameControl(pos);
	outObj->m_texture.loadFromFile("../res/images/next_button.png");
	outObj->m_sprite.setTexture(outObj->m_texture);
	return outObj;
}


NextFrameControl* NextFrameControl::makePreviousFrameButton(const sf::Vector2f &pos)
{
	NextFrameControl* outObj = new NextFrameControl(pos);
	outObj->m_texture.loadFromFile("../res/images/previous_button.png");
	outObj->m_sprite.setTexture(outObj->m_texture);
	return outObj;
}

	
void NextFrameControl::render(sf::RenderTarget *target)
{
	AnimControlButton::render(target);
}


void NextFrameControl::update(sf::Vector2i mousePos, sf::Event &event)
{

	if ( m_shape.getGlobalBounds().contains(mousePos.x, mousePos.y) )
	{
		m_state = Button::state::HOVER;
		m_sprite.setColor( sf::Color(180,180,180) );

		if( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
		{
			m_state = Button::state::ACTIVE;
			m_sprite.setColor( sf::Color(250,250,250) );
		}
	}

	else
	{
		m_state = Button::state::IDLE;
		m_sprite.setColor( sf::Color(150,150,150) );
	}

}
