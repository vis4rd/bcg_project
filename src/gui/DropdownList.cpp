#include "../../include/gui/DropdownList.h"

DropdownList::DropdownList()
:
Button(),
m_background(sf::RectangleShape(sf::Vector2f(m_shape.getSize().x, m_shape.getSize().y / 2))),
m_dropStatus(DropdownList::DropStatus::HIDDEN),
m_currentChoice(0u)
{
	m_background.setPosition(
		sf::Vector2f(
			m_shape.getPosition().x, 
			m_shape.getPosition().y + m_shape.getSize().y
			)//right below the main button
	);
	m_background.setFillColor(sf::Color(255, 255, 255, 80));
}

DropdownList::DropdownList(
	const sf::Vector2f &pos, 
	const sf::Vector2f &size
	)
:
Button(pos, size),
m_background(sf::RectangleShape(sf::Vector2f(size.x, size.y / 2.f))),
m_dropStatus(DropdownList::DropStatus::HIDDEN),
m_currentChoice(0u)
{
	m_background.setPosition(
		sf::Vector2f(
			m_shape.getPosition().x, 
			m_shape.getPosition().y + m_shape.getSize().y
		)//right below the main button
	);
	m_background.setFillColor(sf::Color(255, 255, 255, 80));
}

void DropdownList::addChoice(std::unique_ptr<Button> new_choice)
{
	sf::Vector2f relative_pos = m_background.getPosition();
	if(!m_choices.empty())
	{
		relative_pos = m_choices.back()->getPosition();//set to position of last element
		relative_pos += sf::Vector2f(0.f, m_choices.back()->getSize().y);//shift y with height of last element
		relative_pos += sf::Vector2f(0.f, 3.f);//shift y with 2.f space between choices
	}

	new_choice->setPosition(relative_pos);
	new_choice->setSize(m_shape.getSize());
	new_choice->getShape().setOutlineThickness(0.f);
	m_choices.push_back(std::move(new_choice));

	//new element is appended, now background has to be adjusted in size
	m_background.setSize(
		sf::Vector2f(
			m_shape.getSize().x, 
			m_choices.back()->getPosition().y - m_shape.getPosition().y
		)
	);
}

void DropdownList::addChoice()
{
	this->addChoice(std::make_unique<Button>(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f)));
}

void DropdownList::operator+=(std::unique_ptr<Button> new_choice)
{
	this->addChoice(std::move(new_choice));
}

const sf::RectangleShape &DropdownList::getBackground() const
{
	return m_background;
}

const unsigned short &DropdownList::getDropStatus() const
{
	return m_dropStatus;
}

const unsigned short &DropdownList::getCurrentChoice() const
{
	return m_currentChoice;
}

bool DropdownList::isDropped() const
{
	return (m_dropStatus == DropdownList::DropStatus::DROPPED);
}

void DropdownList::setBackgroundColor(const sf::Color &new_color)
{
	m_background.setFillColor(new_color);
}

void DropdownList::update(sf::Vector2i mousePos, sf::Event &event)
{
	Button::update(mousePos, event);
	if(m_dropStatus == DropdownList::DropStatus::DROPPED)
	{
		unsigned short count = 0u;
		for(auto &it : m_choices)
		{
			it->update(mousePos, event);
			if(it->isPressed())
			{
				m_dropStatus = DropdownList::DropStatus::HIDDEN;
				m_currentChoice = count;
			}
			count++;
		}
	}

	if(m_shape.getGlobalBounds().contains(mousePos.x, mousePos.y)
		&& (event.type == sf::Event::MouseButtonPressed)
		&& (event.mouseButton.button == sf::Mouse::Left))
	{
		if(m_dropStatus == DropdownList::DropStatus::HIDDEN)
        {
        	m_dropStatus = DropdownList::DropStatus::DROPPED;
        }
        else
        {
        	m_dropStatus = DropdownList::DropStatus::HIDDEN;
        }
	}
}

void DropdownList::render(sf::RenderTarget *target)
{
	Button::render(target);
	if(m_dropStatus == DropdownList::DropStatus::DROPPED)
	{
		target->draw(m_background);
		for(auto &it : m_choices)
		{
			it->render(target);
		}
	}
}