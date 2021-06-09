#include "../../include/gui/AnimatedImage.h"

AnimatedImage::AnimatedImage()
:
m_initSize(sf::Vector2f()),
m_initPosition(sf::Vector2f()),
m_verticies(sf::VertexArray(sf::Quads, 4)),
m_texture(nullptr),
m_depth(0.f)
{

}

AnimatedImage::AnimatedImage(const sf::Vector3f &position, std::unique_ptr<sf::Texture> texture, const sf::Vector2f &independent_size)
:
m_initPosition(toV2f(position)),
m_verticies(sf::VertexArray(sf::Quads, 4)),
m_texture(std::move(texture)),
m_depth(0.f)
{
	if(independent_size != sf::Vector2f())
	{
		m_initSize = independent_size;
	}
	else
	{
		m_initSize = static_cast<sf::Vector2f>(m_texture->getSize());
	}

	this->setToInitPosition();
	m_verticies[0].texCoords = sf::Vector2f(0.f, 0.f);
	m_verticies[1].texCoords = sf::Vector2f(m_texture->getSize().x, 0.f);
	m_verticies[2].texCoords = static_cast<sf::Vector2f>(m_texture->getSize());
	m_verticies[3].texCoords = sf::Vector2f(0.f, m_texture->getSize().y);
}

AnimatedImage::AnimatedImage(const AnimatedImage &copy)
:
m_initSize(copy.m_initSize),
m_initPosition(copy.m_initPosition),
m_verticies(copy.m_verticies),
m_texture(std::make_unique<sf::Texture>(*(copy.m_texture.get()))),
m_depth(copy.m_depth)
{

}

const sf::Vector3f AnimatedImage::getPosition() const
{
	return toV3f(m_verticies[0].position);
}

const sf::Vector2f &AnimatedImage::getSize() const
{
	return m_initSize;
}

std::vector<unsigned char> AnimatedImage::getRGB() const
{
	std::vector<unsigned char> result;
	const sf::Image &temp = (*(m_texture.get())).copyToImage();
	const sf::Uint8 *pix = temp.getPixelsPtr();
	unsigned size = static_cast<unsigned>(temp.getSize().x * temp.getSize().y * 4);
	for(unsigned i = 0; i < size; i++)
	{
		result.push_back(pix[i]);
	}
	return result;
}

const float AnimatedImage::getDepth() const
{
	return m_depth;
}

void AnimatedImage::render(sf::RenderTarget *target)
{
	sf::RenderStates states(m_texture.get());
	target->draw(m_verticies, states);
}

//private memebr functions
void AnimatedImage::setToInitPosition()
{
	m_verticies[0].position.x = m_initPosition.x;
	m_verticies[1].position.x = m_initPosition.x + m_initSize.x;
	m_verticies[2].position.x = m_initPosition.x + m_initSize.x;
	m_verticies[3].position.x = m_initPosition.x;

	m_verticies[0].position.y = m_initPosition.y;
	m_verticies[1].position.y = m_initPosition.y;
	m_verticies[2].position.y = m_initPosition.y + m_initSize.y;
	m_verticies[3].position.y = m_initPosition.y + m_initSize.y;

	m_depth = 0.f;
}

const sf::Vector3f AnimatedImage::getVertexPosition(const int &index) const
{
	int uindex = index % m_verticies.getVertexCount(); //unsigned index
	sf::Vector3f result;
	result.x = m_verticies[uindex].position.x;
	result.y = m_verticies[uindex].position.y;
	result.z = 0.f;
	return result;
}

const sf::Vector2f AnimatedImage::toV2f(const sf::Vector3f &origin) const
{
	return sf::Vector2f(origin.x, origin.y);
}

const sf::Vector3f AnimatedImage::toV3f(const sf::Vector2f &origin) const
{
	return sf::Vector3f(origin.x, origin.y, 0.f);
}
