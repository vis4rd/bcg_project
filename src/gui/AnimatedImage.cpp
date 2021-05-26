#include "../../include/gui/AnimatedImage.h"

AnimatedImage::AnimatedImage()
:
m_verticies(sf::VertexArray(sf::Quads, 4)),
m_position({}),
m_transform(em::Matrix4f()),
m_texture(nullptr)
{

}

AnimatedImage::AnimatedImage(const sf::Vector3f &position, std::unique_ptr<sf::Texture> texture)
:
m_verticies(sf::VertexArray(sf::Quads, 4)),
m_texture(std::move(texture))
{
	this->setPosition(position);
	m_verticies[0].texCoords = sf::Vector2f(0.f, 0.f);
	m_verticies[1].texCoords = sf::Vector2f(static_cast<float>(m_texture->getSize().x), 0.f);
	m_verticies[2].texCoords = static_cast<sf::Vector2f>(m_texture->getSize());
	m_verticies[3].texCoords = sf::Vector2f(0.f, static_cast<float>(m_texture->getSize().y));
}

const sf::Vector3f AnimatedImage::getPosition() const
{
	return m_position[0];
}

void AnimatedImage::setPosition(const sf::Vector3f &new_position)
{
	m_position[0] = new_position;
	m_position[1] = sf::Vector3f(new_position.x + m_texture->getSize().x, new_position.y, 0.f);
	m_position[2] = sf::Vector3f(new_position.x + m_texture->getSize().x, new_position.y + m_texture->getSize().y, 0.f);
	m_position[3] = sf::Vector3f(new_position.x, new_position.y + m_texture->getSize().y, 0.f);

	m_verticies[0].position.x = m_position[0].x;
	m_verticies[1].position.x = m_position[1].x;
	m_verticies[2].position.x = m_position[2].x;
	m_verticies[3].position.x = m_position[3].x;

	m_verticies[0].position.y = m_position[0].y;
	m_verticies[1].position.y = m_position[1].y;
	m_verticies[2].position.y = m_position[2].y;
	m_verticies[3].position.y = m_position[3].y;

	m_transform = em::Matrix4f().translate(new_position);
}

void AnimatedImage::render(sf::RenderTarget *target)
{
	sf::RenderStates states(m_texture.get());
	target->draw(m_verticies, states);
}
