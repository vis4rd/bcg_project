#pragma once
#include "Object.h"

/**
 * @brief      Class of simple button.
 */
class Button: public Object
{
public:
    enum state
    {
        LOCKED = 0,
    	IDLE = 1,
    	HOVER = 2,
    	ACTIVE = 3
    };

    /**
     * default constructor
     */
    Button();

    /**
     * @brief      constructor wherein we sets position and size of button
     *
     * @param      pos   The position
     * @param      size  The size
     */
    Button(const sf::Vector2f &pos, const sf::Vector2f &size);
    
    /**
     * @brief      Destructor
     */
    ~Button() =  default;

    /**
     * @brief      Gets the state of button.
     *
     * @return     The state.
     */
    const unsigned short getState() const;

    /**
     * @brief      Sets the state.
     *
     * @param      new_state  The state that will be set
     */
    void setState(const unsigned short new_state);

    /**
     * @brief      Gets information if button is pressed.
     *
     * @return     True if pressed, False otherwise.
     */
    bool isPressed() const;

    /**
     * @brief      Locks the button.
     */
    void lockButton();
    
    /**
     * @brief      Unlocks the button.
     */
    void unlockButton();
    
    /**
     * @brief      Updates state and look of button. 
     *
     * @param      mousePos  The mouse position
     * @param      event     The event
     */
    void update(sf::Vector2i mousePos, sf::Event &event) override;
    
    /**
     * @brief      Renders button in target.
     *
     * @param      target  The target
     */
    void render(sf::RenderTarget *target) override;

protected:
    unsigned short m_state;

};
