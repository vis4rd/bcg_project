#pragma once

#include "../util/ExtendedMath.h"

/**
 * @brief Class applying animations on images
 */
class AnimatedImage
{
public:
	/**
	 * Default constructor
	 * 
	 * Position of the image is set to (0, 0).
	 * Pointer to the texture by default is set to nullptr.
	 */
	AnimatedImage();

	/**
	 * @brief Constructor creating working AnimatedImage object
	 *
	 * @param position The position of an image
	 * @param texture Texture of an image, to which the transformations will be applied
	 */
	explicit AnimatedImage(
		const sf::Vector3f &position, 
		std::unique_ptr<sf::Texture> texture);

	/**
	 * @brief Getter to the position of the AnimatedImage relative to window
	 *
	 * @return (x, y, z) position.
	 * 
	 * If there is not given any initial position while constructing the object,
	 *   the returned position will be (0, 0, 0).
	 * 
	 * Usually z-coordinate will not be of much use, but in very
	 *   rare cases, which SFML does not cover, it might come in handy.
	 */
	const sf::Vector3f getPosition() const;

	/**
	 * @brief Getter to the size of the texture in pixels
	 *
	 * @return The size of the texture
	 * 
	 * If the texture is not given by constructor, the size returned here
	 *   will be (0, 0).
	 */
	const sf::Vector2f &getSize() const;

	/**
	 * @brief Update the transformation matrix of the AnimatedImage
	 *
	 * @param transform 4x4 transform matrix
	 * 
	 * If transform represents an identity matrix, this methods does nothing.
	 * It is also expected to be called very frequently (every frame perhaps).
	 */
	inline void transformUpdate(const em::Matrix4f &transform = em::Matrix4f());

	/**
	 * @brief Renders contents of the AnimatedImage to the target
	 *
	 * @param target Rendering target (ex. window)
	 */
	void render(sf::RenderTarget *target);

private:
	void setToInitPosition();
	const sf::Vector3f getVertexPosition(const int &index) const;
	const sf::Vector2f toV2f(const sf::Vector3f &origin) const;
	const sf::Vector3f toV3f(const sf::Vector2f &origin) const;

	sf::Vector2f m_initSize; ///> Size of the texture set at object definition
	sf::Vector2f m_initPosition; ///> Position of the top-left corner of the texture set at definition
	sf::VertexArray m_verticies; ///> Verticies which transformations are appleid to
	std::unique_ptr<sf::Texture> m_texture; ///> Unique pointer to texture imprinted on verticies
};

inline void AnimatedImage::transformUpdate(const em::Matrix4f &transform)
{
	this->setToInitPosition();
	if(transform != em::Matrix4f())
	{
		em::Matrix4f current = em::Matrix4f().translate(toV3f(m_initPosition));
		sf::Vector3f temp_pos;

		temp_pos = ((current * transform * (-current)) * this->getVertexPosition(0));
		m_verticies[0].position = toV2f(temp_pos);

		temp_pos = ((current * transform * (-current)) * this->getVertexPosition(1));
		m_verticies[1].position = toV2f(temp_pos);

		temp_pos = ((current * transform * (-current)) * this->getVertexPosition(2));
		m_verticies[2].position = toV2f(temp_pos);

		temp_pos = ((current * transform * (-current)) * this->getVertexPosition(3));
		m_verticies[3].position = toV2f(temp_pos);
	}
}
