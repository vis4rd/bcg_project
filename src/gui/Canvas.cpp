#include "../../include/gui/Canvas.h"

Canvas::Canvas()
:
m_plane(),
m_planeBody(sf::Sprite()),
m_objAnim(nullptr),
m_pixAnim(nullptr),
m_animType(Canvas::AnimationType::NONE),
m_startingImage(nullptr),
m_endingImage(nullptr),
m_pixelImage(nullptr),
m_isAnimPlaying(false),
m_currentAnimTime(0.f),
m_totalAnimTime(0.f)
{
	m_plane.create(1.f, 1.f);
}

Canvas::Canvas(const sf::Vector2f &position, const sf::Vector2f &size)
:
m_plane(),
m_planeBody(sf::Sprite()),
m_objAnim(nullptr),
m_pixAnim(nullptr),
m_animType(Canvas::AnimationType::NONE),
m_startingImage(nullptr),
m_endingImage(nullptr),
m_pixelImage(nullptr),
m_isAnimPlaying(false),
m_currentAnimTime(0.f),
m_totalAnimTime(0.f)
{
	m_plane.create(size.x, size.y);
	m_planeBody.setPosition(position);
	//m_planeBody.setScale(size);
}

void Canvas::setAnimation(std::unique_ptr<ObjectAnimation> new_animation)
{
	m_animType = Canvas::AnimationType::OBJ_ANIM;
	this->clearAnimation();
	m_objAnim = std::move(new_animation);
	if(m_startingImage)
	{
		m_startingImage->transformUpdate(m_objAnim->getImage1Frame(m_currentAnimTime));
	}
	if(m_endingImage)
	{
		m_endingImage->transformUpdate(m_objAnim->getImage2Frame(m_currentAnimTime));
	}
}

void Canvas::setAnimation(std::unique_ptr<PixelAnimation> new_animation)
{
	m_animType = Canvas::AnimationType::PIX_ANIM;
	this->clearAnimation();
	m_pixAnim = std::move(new_animation);
	if(m_startingImage && m_pixelImage)//TODO: set pixels according to animation time
	{
		m_pixelImage = std::make_unique<AnimatedImage>(*(m_startingImage.get()));
		m_pixelImage->pixelUpdate(m_pixAnim->getTexture1Frame(m_currentAnimTime));
	}
}

void Canvas::setStartingImage(const sf::String &directory_path)
{
	this->clearStartingImage();
	auto tex = std::make_unique<sf::Texture>();
	tex->loadFromFile(directory_path);
	m_startingImage = std::make_unique<AnimatedImage>(sf::Vector3f(), std::move(tex), static_cast<sf::Vector2f>(m_plane.getSize()));
	if(m_animType == Canvas::AnimationType::OBJ_ANIM)
	{
		if(m_objAnim)
		{
			m_startingImage->transformUpdate(m_objAnim->getStartingTransform1());
		}
		else
		{
			m_startingImage->transformUpdate();
		}
	}
	else if(m_animType == Canvas::AnimationType::PIX_ANIM)//
	{
		if(m_pixAnim)
		{
			m_pixelImage->pixelUpdate(m_pixAnim->getPixels1());
		}
		else
		{
			m_pixelImage->pixelUpdate();
		}
	}
}

void Canvas::setEndingImage(const sf::String &directory_path)
{
	this->clearEndingImage();
	auto tex = std::make_unique<sf::Texture>();
	tex->loadFromFile(directory_path);
	m_endingImage = std::make_unique<AnimatedImage>(sf::Vector3f(), std::move(tex));
	if(m_animType == Canvas::AnimationType::OBJ_ANIM)
	{
		if(m_objAnim)
		{
			m_endingImage->transformUpdate(m_objAnim->getStartingTransform2());
		}
		else
		{
			m_endingImage->transformUpdate();
		}
	}
	else if(m_animType == Canvas::AnimationType::PIX_ANIM)//
	{
		if(m_pixAnim)
		{
			m_pixelImage->pixelUpdate(m_pixAnim->getPixels2());
		}
		else
		{
			m_pixelImage->pixelUpdate();
		}
	}
}

void Canvas::setCurrentAnimationTime(const float &current_time)
{
	if(current_time > 0.f)
	{
		m_currentAnimTime = current_time;
	}
}

void Canvas::setTotalAnimationTime(const float &seconds)
{
	if(seconds > 0.f)
	{
		m_totalAnimTime = seconds;

		if(m_animType == Canvas::AnimationType::OBJ_ANIM)
		{
			m_objAnim->setAnimationLength(seconds);
		}
		else if(m_animType == Canvas::AnimationType::PIX_ANIM)
		{
			m_pixAnim->setAnimationLength(seconds);
		}
	}
}

void Canvas::setAnimationPlayOn(const bool status)
{
	m_isAnimPlaying = status;
}

void Canvas::setSize(const sf::Vector2f &new_size)
{
	m_plane.clear();
	m_plane.create(new_size.x, new_size.y);
}

void Canvas::setPosition(const sf::Vector2f &new_position)
{
	m_planeBody.setPosition(new_position);
}

void Canvas::update(sf::Vector2i mousePos, sf::Event &event)
{
	if(m_isAnimPlaying)
	{
		if(m_animType == Canvas::AnimationType::OBJ_ANIM)
		{
			if(m_startingImage)
			{
				m_startingImage->transformUpdate(m_objAnim->getImage1Frame(m_currentAnimTime));
			}
			if(m_endingImage)
			{
				m_endingImage->transformUpdate(m_objAnim->getImage2Frame(m_currentAnimTime));
			}
		}
		else if(m_animType == Canvas::AnimationType::PIX_ANIM && m_pixelImage)
		{
			m_pixelImage->pixelUpdate(m_pixAnim->getTexture1Frame(m_currentAnimTime));
		}
	}
}

void Canvas::render(sf::RenderTarget *target)
{
	m_plane.clear();

	//Delete this when Canvas' position is set for good
	sf::RectangleShape shape(static_cast<sf::Vector2f>(m_plane.getSize()));
	shape.setFillColor(sf::Color(0, 155, 165));
	m_plane.draw(shape);
	//^^^
	if(m_animType == Canvas::AnimationType::OBJ_ANIM)
	{
		if(m_endingImage)
		{
			m_endingImage->render(&m_plane);
		}
		if(m_startingImage)
		{
			m_startingImage->render(&m_plane);
		}
	}
	else if(m_animType == Canvas::AnimationType::PIX_ANIM && m_pixelImage)
	{
		m_pixelImage->render(&m_plane);
	}

	m_plane.display();
	m_planeBody.setTexture(m_plane.getTexture(), true);
	target->draw(m_planeBody);
}

//private member functions
void Canvas::clearAnimation()
{
	if(m_pixAnim != nullptr)
	{
		m_pixAnim.reset();
	}
	if(m_objAnim != nullptr)
	{
		m_objAnim.reset();
	}
}

void Canvas::clearStartingImage()
{
	if(m_startingImage != nullptr)
	{
		m_startingImage.reset();
	}
}

void Canvas::clearEndingImage()
{
	if(m_endingImage != nullptr)
	{
		m_endingImage.reset();
	}
}
