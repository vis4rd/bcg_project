#pragma once

#include "Panel.h"
#include "ImageButton.h"
#include "DropdownList.h"
#include "TextButton.h"

class PanelButton : public Panel
{

public:
	PanelButton();
	PanelButton(const sf::Vector2f &pos, const sf::Vector2f &size);
	~PanelButton();

	void update(sf::Vector2i mousePos, sf::Event &event) override;
	void render(sf::RenderTarget *target) override;

	ImageButton* getImageUp();
	ImageButton* getImageDown();

	DropdownList* getAnimationChoice();
	DropdownList* getFramesChoice();

	const bool isChanged() const;
	void changesRead();

protected:
	ImageButton *m_imageUp;
	ImageButton *m_imageDown;

	DropdownList *m_animationChoice;
	DropdownList *m_framesChoice;
	
	std::shared_ptr<sf::Font> font;

};