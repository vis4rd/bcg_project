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
	 * @param independent_size Size that is not dependent on texture's size
	 */
	explicit AnimatedImage(
		const sf::Vector3f &position, 
		std::unique_ptr<sf::Texture> texture,
		const sf::Vector2f &independent_size = sf::Vector2f());

	/**
	 * @brief Copy constructor
	 *
	 * @param copy Copied object
	 */
	explicit AnimatedImage(const AnimatedImage &copy);

	/**
	 * @brief Getter to the size of the texture in pixels
	 *
	 * @return The size of the texture
	 * 
	 * If the texture is not given by constructor, the size returned here
	 *   will be (0, 0).
	 */
	sf::Vector2u getSize() const;

	/**
	 * @brief Get the vector of RGB values of the texture
	 *
	 * @return The vector filled with RGB values
	 */
	std::vector<unsigned char> getRGB() const;

	/**
	 * @brief Getter to array of depth of all image's verticies
	 *
	 * @return Array of Floating point values, the higher they are, the "deeper" is the vertex
	 * 
	 * AnimatedImages are rendered in order of most to least deep.
	 */
	std::array<float, 4> getDepths() const;

	/**
	 * @brief Getter to depth of a vertex under specific index
	 *
	 * @param index The index which indicated what vertex of the AnimatedImage is of interest
	 *
	 * @return The depth of the chosen vertex
	 * 
	 * Verticies' indices are set from 0 to 3 from top-left corner clockwise.
	 */
	const float &getVertexDepth(const unsigned index) const;

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
	 * @brief Update texture pixels of the AnimatedImage
	 *
	 * @param pixels vector of RGBA values of the texture
	 */
	inline void pixelUpdate(std::vector<unsigned char> pixels = {});

	/**
	 * @brief Renders contents of the AnimatedImage to the target
	 *
	 * @param target Rendering target (ex. window)
	 */
	void render(std::shared_ptr<sf::RenderTarget> target);

private:
	//const sf::Vector3f getVertexPosition(const int &index) const;
	const sf::Vector2f toV2f(const sf::Vector3f &origin) const;
	const sf::Vector3f toV3f(const sf::Vector2f &origin) const;

	sf::VertexArray m_verticies; ///> Verticies defining AnimatedImage's shape
	std::array<sf::Vector3f, 4> m_initialPosition; ///> 3-dimensional initial position in local coordinates
	std::array<sf::Vector3f, 4> m_currentPosition; ///> 3-dimensional current position in local coordinates
	std::unique_ptr<sf::Texture> m_initialTexture; ///> Unique pointer to texture imprinted on verticies
	std::unique_ptr<sf::Texture> m_currentTexture; ///> Unique pointer to texture imprinted on verticies
	sf::Vector2u m_canvasSize;
};

template <typename T>
sf::Vector3<T> operator*(const sf::Vector3<T>& left, const sf::Vector2<T>& right)
{
	sf::Vector3<T> result(left.x * right.x, left.y * right.y, left.z);
	return result;
}

template <typename T>
sf::Vector3<T>& operator/=(sf::Vector3<T>& left, const sf::Vector3<T>& right)
{
	left.x /= right.x;
	left.y /= right.y;
	left.z /= right.z;
	return left;
}

template <typename T>
int signof(const T &target)
{
	return (T(0) < target) - (target < T(0));
}

inline void AnimatedImage::transformUpdate(const em::Matrix4f &transform)
{
	m_currentPosition[0] = m_initialPosition[0];
	m_currentPosition[1] = m_initialPosition[1];
	m_currentPosition[2] = m_initialPosition[2];
	m_currentPosition[3] = m_initialPosition[3];

	if(transform != em::Matrix4f())
	{
		//transform
		m_currentPosition[0] = transform * (m_currentPosition[0] * (sf::Vector2f(m_canvasSize)/2.f));
		m_currentPosition[1] = transform * (m_currentPosition[1] * (sf::Vector2f(m_canvasSize)/2.f));
		m_currentPosition[2] = transform * (m_currentPosition[2] * (sf::Vector2f(m_canvasSize)/2.f));
		m_currentPosition[3] = transform * (m_currentPosition[3] * (sf::Vector2f(m_canvasSize)/2.f));

		//normalize
		m_currentPosition[0] /= sf::Vector3f(m_canvasSize.x/2.f, m_canvasSize.y/2.f, 1.f);
		m_currentPosition[1] /= sf::Vector3f(m_canvasSize.x/2.f, m_canvasSize.y/2.f, 1.f);
		m_currentPosition[2] /= sf::Vector3f(m_canvasSize.x/2.f, m_canvasSize.y/2.f, 1.f);
		m_currentPosition[3] /= sf::Vector3f(m_canvasSize.x/2.f, m_canvasSize.y/2.f, 1.f);
	}

	m_verticies[0].position.x = (m_canvasSize.x/2.f) + ((m_canvasSize.x/2.f) * m_currentPosition[0].x / std::pow(std::abs(1.f + m_currentPosition[0].z/200.f), signof(m_currentPosition[0].z)));
	m_verticies[0].position.y = (m_canvasSize.y/2.f) + ((m_canvasSize.y/2.f) * m_currentPosition[0].y / std::pow(std::abs(1.f + m_currentPosition[0].z/200.f), signof(m_currentPosition[0].z)));
	m_verticies[1].position.x = (m_canvasSize.x/2.f) + ((m_canvasSize.x/2.f) * m_currentPosition[1].x / std::pow(std::abs(1.f + m_currentPosition[1].z/200.f), signof(m_currentPosition[1].z)));
	m_verticies[1].position.y = (m_canvasSize.y/2.f) + ((m_canvasSize.y/2.f) * m_currentPosition[1].y / std::pow(std::abs(1.f + m_currentPosition[1].z/200.f), signof(m_currentPosition[1].z)));
	m_verticies[2].position.x = (m_canvasSize.x/2.f) + ((m_canvasSize.x/2.f) * m_currentPosition[2].x / std::pow(std::abs(1.f + m_currentPosition[2].z/200.f), signof(m_currentPosition[2].z)));
	m_verticies[2].position.y = (m_canvasSize.y/2.f) + ((m_canvasSize.y/2.f) * m_currentPosition[2].y / std::pow(std::abs(1.f + m_currentPosition[2].z/200.f), signof(m_currentPosition[2].z)));
	m_verticies[3].position.x = (m_canvasSize.x/2.f) + ((m_canvasSize.x/2.f) * m_currentPosition[3].x / std::pow(std::abs(1.f + m_currentPosition[3].z/200.f), signof(m_currentPosition[3].z)));
	m_verticies[3].position.y = (m_canvasSize.y/2.f) + ((m_canvasSize.y/2.f) * m_currentPosition[3].y / std::pow(std::abs(1.f + m_currentPosition[3].z/200.f), signof(m_currentPosition[3].z)));

	/*std::cout << "[0] (top-left) = (" << m_currentPosition[0].x << ", " << m_currentPosition[0].y << ", " << m_currentPosition[0].z << ")" << std::endl
			<< "[1] (top-right) = (" << m_currentPosition[1].x << ", " << m_currentPosition[1].y << ", " << m_currentPosition[1].z << ")" << std::endl
			<< "[2] (bottom-right) = (" << m_currentPosition[2].x << ", " << m_currentPosition[2].y << ", " << m_currentPosition[2].z << ")" << std::endl
			<< "[3] (bottom-left) = (" << m_currentPosition[3].x << ", " << m_currentPosition[3].y << ", " << m_currentPosition[3].z << ")" << std::endl
			<< std::endl;*/
}

inline void AnimatedImage::pixelUpdate(std::vector<unsigned char> pixels)
{
	if(m_initialTexture && (pixels.size() > 0))
	{
		m_currentTexture = std::make_unique<sf::Texture>(*m_initialTexture);
		sf::Vector2u size = m_currentTexture->getSize();
		pixels.resize(size.x * size.y * 4);
		m_currentTexture->update(pixels.data(), size.x, size.y, 0.f, 0.f);
	}
}
