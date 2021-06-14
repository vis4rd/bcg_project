#pragma once

#include "../root/Root.h"

/**
 * @brief Abstract class describing all objects appearing on the screen
 */
class Object
{
public:
	/**
	 * @brief Default Constructor
	 *
	 * @param pos The position of the object
	 * @param size The size of the object
	 */
	Object(const sf::Vector2f &pos = sf::Vector2f(0.f, 0.f), const sf::Vector2f &size = sf::Vector2f(0.f, 0.f));
	
	/**
	 * @brief Copy constructor
	 *
	 * @param copy Copied object
	 */
	Object(const Object &copy);

	/**
	 * @brief Move constructor
	 *
	 * @param source Source object
	 */
	Object(Object &&source);

	/**
	 * @brief Default destructor
	 */
	virtual ~Object() = default;

	//getters/setters/checkers
	
	/**
	 * @brief Getter to the position of the object
	 *
	 * @return The (x, y) position relative to the window.
	 */
	virtual const sf::Vector2f &getPosition() const;

	/**
	 * @brief Getter to the size of the object
	 *
	 * @return The (x, y) size of the object.
	 */
	virtual const sf::Vector2f &getSize() const;

	/**
	 * @brief Getter to rectangle defining object's shape
	 *
	 * @return Rectangle defining object's shape.
	 */
	virtual sf::RectangleShape &getShape();

	/**
	 * @brief Setter of the object's position
	 *
	 * @param pos The new position of the object.
	 */
	virtual void setPosition(const sf::Vector2f &pos);

	/**
	 * @brief Setter of the object's size
	 *
	 * @param size The new size of the object.
	 */
	virtual void setSize(const sf::Vector2f &size);

	/**
	 * @brief Pure virtual method drawing deriving classes' objects to the target
	 *
	 * @param target The target which shapes and objects are rendered to.
	 */
	virtual void render(sf::RenderTarget *target) = 0;

	/**
	 * @brief Pure virtual method updating contents of the deriving classes
	 *
	 * @param mousePos The mouse position relative to the screen
	 * @param event The event reference handling all events in the window
	 */
	virtual void update(sf::Vector2i mousePos, sf::Event &event) = 0;

protected:
	sf::RectangleShape m_shape;///> Rectangle defining object's shape

private:

};
