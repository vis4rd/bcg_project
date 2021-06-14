#pragma once

#include "Panel.h"
#include "ImageButton.h"
#include "DropdownList.h"
#include "TextButton.h"
#include "SaveButton.h"
/**
 * @brief      Class responsible for handling and displaying ImageButtons,SaveButton and DropdownLists
 */
class PanelButton : public Panel
{

public:
	/**
	 * @brief      Constructor responsible for setting postions and sizes of two ImageButtons and two DropdownList
	 * 			   also sets the options available for selection in DropdownLists
	 * 
	 *
	 * @param[in]  pos   The position of whole panel
	 * @param[in]  size  The size of whole panel
	 */	
	PanelButton(const sf::Vector2f &pos, const sf::Vector2f &size);
	/**
	 * @brief      destructor deleting every allocated object
	
	~PanelButton();
	 /**
     * @brief Class responsible for updating every individual object in PanelButton
     *
     * @param mousePos The current mouse position 
     * @param event The event hedning clicking on the Panel
     */
	void update(sf::Vector2i mousePos, sf::Event &event) override;
	/**
	 * @brief Renders this instance of the PanelButtons on sf::RenderTarget.
	 *
	 * @param target The target which the PanelButton is rendered on.
	 */
	void render(sf::RenderTarget *target) override;
	/**
	 * @brief      Getter of the first image
	 *
	 * @return     The first image.
	 */
	ImageButton* getImageUp();
	/**
	 * @brief      Getter of the second image
	 *
	 * @return     The second image.
	 */
	ImageButton* getImageDown();
	/**
	 * @brief      Getter of the saveButton
	 *
	 * @return     The save button.
	 */
	SaveButton* getSaveButton();
	/**
	 * @brief      Getter for the DropdownList handling animation choices
	 *
	 * @return     The DropdownList handling animation choices.
	 */
	DropdownList* getAnimationChoice();
	/**
	 * @brief      Getter for the DropdownList handling frames choices
	 *
	 * @return     The DropdownList handling frames choices.
	 */
	DropdownList* getFramesChoice();
	/**
	 * @brief      Function checking if there has been any change in any of the objects,calls the "isChanged()" method for each object
	 *
	 * @return     True if changed, False otherwise.
	 */
	const bool isChanged() const;
	/**
	 * @brief      function calling the methods "changesRead" of every single object
	 */
	void changesRead();

protected:
	ImageButton *m_imageUp; //new ImageButton handling first Image
	ImageButton *m_imageDown; //new ImageButton handling second Image
	SaveButton *m_saveButton; //new SaveButton handling saving every frame to file

	DropdownList *m_animationChoice;//new DropdownList handling selection of animation
	DropdownList *m_framesChoice;//new DropdownList handling selection of quantity of frames
	
	std::shared_ptr<sf::Font> font;

};