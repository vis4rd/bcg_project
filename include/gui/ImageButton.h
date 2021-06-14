#pragma once

#include "Button.h"
/**
 * @brief      Class responsible for loading two images selected by the user to the program
 * 			   and displaying those images on auxiliary windows
 */
class ImageButton : public Button
{
public:
	/**
	 * default constructor
	 */
	ImageButton();
	/**
	 * @brief      Constructor setting starting parameters of ImageButtons such as:
	 * 			   color,postion,thickness,default image,scale
	 *
	 * @param[in]  pos   The position
	 * @param[in]  size  The size
	 */
	ImageButton(const sf::Vector2f &pos, const sf::Vector2f &size);

	/**
	 * @brief      Copying constructor
	 *
	 * @param[in]  Reference to ImageButton object
	 */
	ImageButton(const ImageButton &copy);

	/**
	 * @brief      Move constructor
	 *
	 * @param      Reference to rvalue
	 */
	ImageButton(ImageButton &&source);

	/**
	 * @brief      Overrided function which renders(draws) the given target.
	 *
	 * @param      RenderTarget The target on which the instatntion is rendered
	 */
	void render(sf::RenderTarget *target) override;

	/**
     * @brief Method responsible for chosing the image from user's files, and displaying it on the auxiliary window
     *
     * @param mousePos The current mouse position 
     * @param event The event hedning clicing of the ImageButtion 
     */
	void update(sf::Vector2i mousePos, sf::Event &event) override;

	/**
	 * @brief      Returns the path to the chosen by user image.
	 */
	std::string getPath();

	/**
	 * @brief      Checks whether the image chosen by the user was chosen successfully(good extension e.t.c)
	 *
	 * @return     True if succesfully, False otherwise.
	 */
	const bool isChanged() const;

	/**
	 * @brief     Function setting m_isChange on false, used by another class which uses ImageButton
	 */
	void changeRead();

private:
	sf::Sprite m_spr; //sprite
	sf::Texture m_texture; //texture
	std::string m_path; //string storing path to the image chosen by user
	bool m_isChanged;	//bool type, true if user has selected a photo, false if user selected nothing
};	
