#include "../../include/gui/AnimatedImage.h"

// DEBUG
/*void pVev2(const sf::Vector2f &vec)
{
	std::cout << "(" << vec.x << ", " << vec.y << ")";
}*/
//

AnimatedImage::AnimatedImage()
:
m_verticies(sf::TriangleFan, 4),
m_initialPosition({}),
m_currentPosition({}),
m_initialTexture(nullptr),
m_currentTexture(nullptr),
m_canvasSize(sf::Vector2f())
{

}

AnimatedImage::AnimatedImage(const sf::Vector3f &position, std::unique_ptr<sf::Texture> texture, const sf::Vector2f &independent_size)
:
m_verticies(sf::TriangleFan, 4),
m_initialPosition({}),
m_currentPosition({}),
m_initialTexture(std::move(texture)),
m_currentTexture(std::make_unique<sf::Texture>(*m_initialTexture))
{
	if(independent_size != sf::Vector2f())
	{
		m_initialPosition[0] = this->toV3f(-independent_size/2.f); // top-left corner
		m_initialPosition[2] = this->toV3f(independent_size/2.f); // bottom-right corner
		m_initialPosition[1] = this->toV3f(sf::Vector2f(independent_size.x, -independent_size.y)/2.f); // top-right corner
		m_initialPosition[3] = this->toV3f(sf::Vector2f(-independent_size.x, independent_size.y)/2.f); // bottom-left corner
		m_canvasSize = static_cast<sf::Vector2u>(independent_size);
	}
	else
	{
		m_initialPosition[0] = this->toV3f(-static_cast<sf::Vector2f>(m_initialTexture->getSize())/2.f); // top-left corner
		m_initialPosition[2] = this->toV3f(static_cast<sf::Vector2f>(m_initialTexture->getSize())/2.f); // bottom-right corner
		m_initialPosition[1] = this->toV3f(sf::Vector2f(m_initialTexture->getSize().x, -m_initialTexture->getSize().y)/2.f); // top-right corner
		m_initialPosition[3] = this->toV3f(sf::Vector2f(-m_initialTexture->getSize().x, m_initialTexture->getSize().y)/2.f); // bottom-left corner
		m_canvasSize = m_initialTexture->getSize();
	}
	m_initialPosition[0].z = position.z;
	m_initialPosition[1].z = position.z;
	m_initialPosition[2].z = position.z;
	m_initialPosition[3].z = position.z;

	m_currentPosition[0] = m_initialPosition[0];
	m_currentPosition[1] = m_initialPosition[1];
	m_currentPosition[2] = m_initialPosition[2];
	m_currentPosition[3] = m_initialPosition[3];

	m_verticies[0].position.x = (m_canvasSize.x/2.f) + (m_currentPosition[0].x / std::abs(1.f + m_currentPosition[0].z/2.f));
	m_verticies[0].position.y = (m_canvasSize.y/2.f) + (m_currentPosition[0].y / std::abs(1.f + m_currentPosition[0].z/2.f));
	m_verticies[1].position.x = (m_canvasSize.x/2.f) + (m_currentPosition[1].x / std::abs(1.f + m_currentPosition[1].z/2.f));
	m_verticies[1].position.y = (m_canvasSize.y/2.f) + (m_currentPosition[1].y / std::abs(1.f + m_currentPosition[1].z/2.f));
	m_verticies[2].position.x = (m_canvasSize.x/2.f) + (m_currentPosition[2].x / std::abs(1.f + m_currentPosition[2].z/2.f));
	m_verticies[2].position.y = (m_canvasSize.y/2.f) + (m_currentPosition[2].y / std::abs(1.f + m_currentPosition[2].z/2.f));
	m_verticies[3].position.x = (m_canvasSize.x/2.f) + (m_currentPosition[3].x / std::abs(1.f + m_currentPosition[3].z/2.f));
	m_verticies[3].position.y = (m_canvasSize.y/2.f) + (m_currentPosition[3].y / std::abs(1.f + m_currentPosition[3].z/2.f));

	/*std::cout << "ANIMATED IMAGE(" << std::endl;
	std::cout << "top-left = "; pVev2(m_verticies[0].position); std::cout << std::endl;
	std::cout << "top-right = "; pVev2(m_verticies[1].position); std::cout << std::endl;
	std::cout << "bottom-left = "; pVev2(m_verticies[2].position); std::cout << std::endl;
	std::cout << "bottom-right = "; pVev2(m_verticies[3].position); std::cout << std::endl;
	std::cout << ")" << std::endl << std::endl;*/
}

AnimatedImage::AnimatedImage(const AnimatedImage &copy)
:
m_verticies(copy.m_verticies),
m_initialTexture(std::make_unique<sf::Texture>(*(copy.m_initialTexture))),
m_currentTexture(std::make_unique<sf::Texture>(*(copy.m_currentTexture))),
m_canvasSize(copy.m_canvasSize)
{
	std::copy(copy.m_initialPosition.begin(), copy.m_initialPosition.end(), m_initialPosition.begin());
	std::copy(copy.m_currentPosition.begin(), copy.m_currentPosition.end(), m_currentPosition.begin());
}

sf::Vector2u AnimatedImage::getSize() const
{
	return m_initialTexture->getSize();
}

std::vector<unsigned char> AnimatedImage::getRGB() const
{
	std::vector<unsigned char> result;
	const sf::Image &temp = (*(m_currentTexture.get())).copyToImage();
	const sf::Uint8 *pix = temp.getPixelsPtr();
	unsigned size = static_cast<unsigned>(temp.getSize().x * temp.getSize().y * 4);
	for(unsigned i = 0; i < size; i++)
	{
		result.push_back(pix[i]);
	}
	return result;
}

std::array<float, 4> AnimatedImage::getDepths() const
{
	std::array<float, 4> result{};
	result[0] = m_currentPosition[0].z;
	result[1] = m_currentPosition[1].z;
	result[2] = m_currentPosition[2].z;
	result[3] = m_currentPosition[3].z;
	return result;
}

const float &AnimatedImage::getVertexDepth(const unsigned index) const
{
	if(index >= 4)
	{
		throw std::out_of_range("const float &AnimatedImage::getVertexDepth(const unsigned) const: Given index is of value " + std::to_string(index) + "while size of an array is 4.");
	}
	else
	{
		return m_currentPosition[index].z;
	}
}

void AnimatedImage::render(std::shared_ptr<sf::RenderTarget> target)
{
	sf::RenderStates states(m_currentTexture.get());
	target->draw(m_verticies, states);
}

const sf::Vector2f AnimatedImage::toV2f(const sf::Vector3f &origin) const
{
	return sf::Vector2f(origin.x, origin.y);
}

const sf::Vector3f AnimatedImage::toV3f(const sf::Vector2f &origin) const
{
	return sf::Vector3f(origin.x, origin.y, 0.f);
}

