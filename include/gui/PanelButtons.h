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

protected:

	ImageButton *m_imageUp;
	ImageButton *m_imageDown;

	DropdownList *m_dropdownUp;
	DropdownList *m_dropdownDown;
	
	std::shared_ptr<sf::Font> font;


	//jakiś wskaźnik żeby przekazac aktualne zdjęcie do animacji?
};