#pragma once

#include "Button.h"

class TextButton : public Button
{
public:
    /**
     * @brief Default Contructor
     * 
     * Font is neither defined nor set. After use of this constructor
     *   for TextButton to work, calling setFont(std::shared_ptr<sf::Font> new_font)
     *   is required.
     * 
     * Font size is by default set to 1/3 of TextButton's height. To change it, 
     *   use setFontSize(const unsigned int &pixels).
     *   
     * Text label is centered.
     */
	TextButton();

    /**
     * @brief Contructor setting position, size, font and label's text of the TextButton
     *
     * @param pos The position of the TextButton
     * @param size The size of the TextButton
     * @param font The font diplayed on the TextButton's label
     * @param label String displayed on a TextButton
     * 
     * @note Size of the TextButton should not be 0x0 or the default font size
     *       will be undefined.
     * 
     * If the font parameter is nullptr, there will be a new font constructed in
     *   it's place. On the other hand, if no actual font was loaded into it, 
     *   TextButton will attempt to find a replacement in res/fonts directory.
     *   
     * Font size is by default set to 1/3 of TextButton's height. To change it, 
     *   use setFontSize(const unsigned int &pixels).
     *   
     * If no string parameter is provided or it is empty, the label text will be
     *   set to "undefined".
     *   
     * Text label is centered.
     */
    explicit TextButton(const sf::Vector2f &pos, const sf::Vector2f &size, std::shared_ptr<sf::Font> font, const sf::String &label = sf::String());
    
    /**
     * @brief Default destructor
     * 
     * @note Note that given font will not be deleted unless all shared_pointers
     *       are destroyed or reset().
     */
    ~TextButton() =  default;

    /**
     * @brief Gets the label's text string of the TextButton
     *
     * @return Const reference to sf::String object
     */
    const sf::String &getLabel() const;

    /**
     * @brief Gets an sf::Text object displaying TextButton's label
     *
     * @return Const reference to sf::Text object
     */
    const sf::Text &getText() const;

    /**
     * @brief Sets the text string visible on the TextButton
     *
     * @param new_label Label's new text
     */
    void setLabel(const sf::String &new_label);

    /**
     * @brief Sets the size of the TextButton
     *
     * @param new_size The new size of the TextButton
     * 
     * The new size can not be bigger than button's height, therefore
     *   if it is, the value will be properly adjusted.
     * 
     * The Button's member function is overloaded so that the text
     *   visible on the TextButton can be properly centered.
     */
    void setSize(const sf::Vector2f &new_size) override;

    /**
     * @brief Sets the position of the TextButton
     *
     * @param new_pos The new position of the TextButton
     * 
     * The Button's member function is overloaded so that the text visible 
     *   on the TextButton can be properly adjusteed to buttons position.
     */
    void setPosition(const sf::Vector2f &new_pos) override;

    /**
     * @brief Sets the font to the given one.
     *
     * @param new_font The new font that will be displayed on TextButton
     * 
     * If the given new_font parameter is nullptr, this will throw 
     *   an exception. Otherwise, if no actual font was loaded into it, 
     *   TextButton will attempt to find a replacement in res/fonts 
     *   directory. 
     */
    virtual void setFont(std::shared_ptr<sf::Font> new_font);

    /**
     * @brief Sets the size of the TextButton's font
     *
     * @param pixels The size of text characters in pixels
     */
    void setFontSize(const unsigned int &pixels);

    /**
     * @brief Updates all contents of TextButton's instance
     *
     * @param mousePos The current mouse position relevant to app's window
     * @param event The event handling clicking on the TextButton
     */
    void update(sf::Vector2i mousePos, sf::Event &event) override;

    /**
     * @brief Renders this instance of the TextButton on sf::RenderTarget.
     *
     * @param target The target which the TextButton is rendered on.
     */
    void render(sf::RenderTarget *target) override;

protected:
	std::shared_ptr<sf::Font> m_font;
	sf::Text m_label;

private:
	void centerText();

};