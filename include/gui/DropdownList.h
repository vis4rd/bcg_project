#pragma once

#include "Button.h"

class DropdownList final : public Button
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
	 * 
	 * Subbuttons in the dropdown have the same size as the main button.
	 * Every another appended Button is positioned under the main button.
	 */
	explicit DropdownList(const sf::Vector2f &pos, const sf::Vector2f &size);

	/**
	 * @brief Default Destructor
	 * 
	 * Allocated memory is taken care of thanks to std::unique_ptr;
	 */
	virtual ~DropdownList() = default;

	/**
	 * @brief Appends a new Button to the dropdown.
	 *
	 * @param new_choice Unique pointer to the Button instance
	 * 
	 * If new_choice is the first one to be appended (dropdown is empty),
	 *   it is positioned right under the main button. 
	 * 
	 * Every another Button goes under the last one.
	 * 
	 * new_choice's size is exactly the same as the size of the main button.
	 */
	void addChoice(std::unique_ptr<Button> new_choice);

	/**
	 * @brief Appends created in-place Button to the dropdown.
	 * 
	 * This method is provided for convenience.
	 */
	void addChoice();

	/**
	 * @brief Appends a new Button to the dropdown.
	 *
	 * @param new_choice Unique pointer to the Button instance.
	 * 
	 * This method is provided for convenience.
	 */
	void operator+=(std::unique_ptr<Button> new_choice);

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
	void render(sf::RenderTarget *target) override;

private:
	sf::RectangleShape m_background;
	unsigned short m_dropStatus;
	std::vector<std::unique_ptr<Button>> m_choices;
	unsigned short m_currentChoice;
};