#pragma once

#include "TextButton.h"

class DropdownList final : public TextButton
{
public:
	/**
	 * @brief Status of dropdown's visibility
	 * 
	 * If m_dropStatus is set to HIDDEN then only main button is rendered.
	 * If m_dropStatus is set to DROPPED then all contents of the dropdown is visible.
	 */
	enum DropStatus
	{
		HIDDEN = 0,
		DROPPED = 1
	};

	/**
	 * @brief Default Constructor
	 * 
	 * Initial position and size are set to (x, y) = (0, 0).
	 * Background color is set to rgba(255, 255, 255, 80).
	 */
	DropdownList();

	/**
	 * @brief Contructor setting position and size of the main button
	 *
	 * @param pos The position of the main button
	 * @param size The size of the main button
	 * @param font The font diplayed in TextButton's label
	 * @param label String displayed on a TextButton
	 * 
	 * Subbuttons in the dropdown have the same size as the main button.
	 * Every another appended TextButton is positioned under the main button.
	 */
	explicit DropdownList(const sf::Vector2f &pos, const sf::Vector2f &size, std::shared_ptr<sf::Font> font, const sf::String &label = sf::String());

	/**
	 * @brief Default Destructor
	 * 
	 * Allocated memory is taken care of thanks to std::unique_ptr;
	 */
	virtual ~DropdownList() = default;

	/**
	 * @brief Appends a new TextButton to the dropdown.
	 *
	 * @param new_choice Unique pointer to the TextButton instance
	 * 
	 * If new_choice is the first one to be appended (dropdown is empty),
	 *   it is positioned right under the main button. 
	 * 
	 * Every another TextButton goes under the last one.
	 * 
	 * new_choice's size is exactly the same as the size of the main button.
	 */
	void addChoice(std::unique_ptr<TextButton> new_choice);

	/**
	 * @brief Appends created in-place TextButton to the dropdown.
	 * 
	 * @param String which will be visible on the TextButton
	 * 
	 * This method is provided for convenience.
	 */
	void addChoice(const sf::String &label);

	/**
	 * @brief Appends a new TextButton to the dropdown.
	 *
	 * @param new_choice Unique pointer to the Button instance.
	 * 
	 * This method is provided for convenience.
	 */
	void operator+=(std::unique_ptr<TextButton> new_choice);

	void changeRead();

	const bool isChanged() const;

	/**
	 * @brief Getter to the background of buttons in the dropdown.
	 *
	 * @return Const reference to m_background field.
	 */
	const sf::RectangleShape &getBackground() const;

	/**
	 * @brief Getter to the current status of dropdown's visibility.
	 *
	 * @return Const reference to m_dropStatus.
	 */
	const unsigned short &getDropStatus() const;

	/**
	 * @brief Getter to the index of the chosen option in the dropdown.
	 *
	 * @return Const reference to m_currentChoice.
	 * 
	 * Buttons appended to the dropdown are numerated per order of addition.
	 * It means that the first Button (exluding the main one) has index 0, 
	 *   second one has 1 etc...
	 * Button with index 0 is always positioned at the top of the dropdown
	 *   (right below the main Button).
	 */
	const unsigned short &getCurrentChoice() const;

	/**
	 * @brief Checks whether dropdown is in DROPPED status.
	 *
	 * @return True if DROPPED, false otherwise.
	 */
	bool isDropped() const;

	/**
	 * @brief Sets the background color of the dropdown.
	 *
	 * @param new_color A new color of the background.
	 */
	void setBackgroundColor(const sf::Color &new_color);

	/**
	 * @brief Updates all contents of the dropdown instance.
	 *
	 * @param mousePos Mouse position relevant to app's window.
	 * @param event Event handling clicking of dropdown's buttons.
	 */
	void update(sf::Vector2i mousePos, sf::Event &event) override;

	/**
	 * @brief Renders this instance of the dropdown on sf::RenderTarget.
	 *
	 * @param target The target which the dropdown is rendered on.
	 */
	void render(std::shared_ptr<sf::RenderTarget> target) override;

private:
	sf::RectangleShape m_background;
	unsigned short m_dropStatus;
	std::vector<std::unique_ptr<TextButton>> m_choices;
	unsigned short m_currentChoice;

	bool m_isChanged;
};
