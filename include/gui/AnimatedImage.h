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
	 * Usually z-coordinate will not be of much use, but in very
	 *   rare cases, which SFML does not cover, it might come in handy.
	 */
	const sf::Vector3f getPosition() const;

	/**
	 * @brief Setter of the position of the AnimatedImage relative to window
	 *
	 * @param new_position New position of the object
	 */
	void setPosition(const sf::Vector3f &new_position);

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
	sf::VertexArray m_verticies; ///> Verticies which follow the transformation data
	std::array<sf::Vector3f, 4u> m_position; ///> The position of every vertex.
	em::Matrix4f m_transform; ///> 4x4 matrix containing current transformations of the object
	std::unique_ptr<sf::Texture> m_texture; ///> Unique pointer to texture applied to verticies
};

inline void AnimatedImage::transformUpdate(const em::Matrix4f &transform)
{
	if(transform != em::Matrix4f())
	{
		m_position[0] = (m_transform * transform * (-m_transform) * m_position[0]);
		m_position[1] = (m_transform * transform * (-m_transform) * m_position[1]);
		m_position[2] = (m_transform * transform * (-m_transform) * m_position[2]);
		m_position[3] = (m_transform * transform * (-m_transform) * m_position[3]);

		m_verticies[0].position.x = m_position[0].x;
		m_verticies[0].position.y = m_position[0].y;
		m_verticies[1].position.x = m_position[1].x;
		m_verticies[1].position.y = m_position[1].y;
		m_verticies[2].position.x = m_position[2].x;
		m_verticies[2].position.y = m_position[2].y;
		m_verticies[3].position.x = m_position[3].x;
		m_verticies[3].position.y = m_position[3].y;

		m_transform = em::Matrix4f().translate(m_position[0]);	
	}
}
