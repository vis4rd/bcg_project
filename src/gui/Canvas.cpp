#include "../../include/gui/Canvas.h"
#include "../../include/program/Program.h"

Canvas::Canvas()
:
m_plane(),
m_planeBody(sf::Sprite()),
m_objAnim(nullptr),
m_pixAnim(nullptr),
m_animType(Canvas::AnimationType::NONE),
m_startingImage(nullptr),
m_endingImage(nullptr),
m_pixelImageIn(nullptr),
m_pixelImageOut(nullptr),
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
m_pixelImageIn(nullptr),
m_pixelImageOut(nullptr),
m_isAnimPlaying(false),
m_currentAnimTime(0.f),
m_totalAnimTime(0.f)
{
	m_plane.create(size.x, size.y);
	m_planeBody.setPosition(position);
}

void Canvas::setAnimation(std::unique_ptr<ObjectAnimation> new_animation)
{
	m_animType = Canvas::AnimationType::OBJ_ANIM;
	this->clearAnimation();
	m_objAnim = std::move(new_animation);

	em::Matrix4f perspective(	0.f, 0.f, 1.f, 0.f,
								0.f, 0.f, -1.f, 0.f,
								0.f, 0.f, -1.f, 0.f,
								0.f, 0.f, -1.f, 0.f);
	if(m_startingImage)
	{
		m_startingImage->transformUpdate(m_objAnim->getImage1Frame(m_currentAnimTime) * perspective);
	}
	if(m_endingImage)
	{
		m_endingImage->transformUpdate(m_objAnim->getImage2Frame(m_currentAnimTime) * perspective);
	}
}

void Canvas::setAnimation(std::unique_ptr<PixelAnimation> new_animation)
{
	m_animType = Canvas::AnimationType::PIX_ANIM;
	this->clearAnimation();
	m_pixAnim = std::move(new_animation);

	if(m_startingImage)
	{
		m_startingImage->transformUpdate();
		m_pixelImageIn = std::make_unique<AnimatedImage>(*(m_startingImage.get()));
		m_pixAnim->setPixels1(m_startingImage->getRGB());
		m_pixelImageIn->pixelUpdate(m_pixAnim->getTexture1Frame(m_currentAnimTime));
	}
	if(m_endingImage)
	{
		m_endingImage->transformUpdate();
		m_pixelImageOut = std::make_unique<AnimatedImage>(*(m_endingImage.get()));
		m_pixAnim->setPixels2(m_endingImage->getRGB());
		m_pixelImageOut->pixelUpdate(m_pixAnim->getTexture2Frame(m_currentAnimTime));
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
			m_pixelImageIn->pixelUpdate(m_pixAnim->getPixels1());
		}
		else
		{
			m_pixelImageIn->pixelUpdate();
		}
	}
}

void Canvas::setEndingImage(const sf::String &directory_path)
{
	this->clearEndingImage();
	auto tex = std::make_unique<sf::Texture>();
	tex->loadFromFile(directory_path);
	m_endingImage = std::make_unique<AnimatedImage>(sf::Vector3f(), std::move(tex), static_cast<sf::Vector2f>(m_plane.getSize()));
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
	else if(m_animType == Canvas::AnimationType::PIX_ANIM)
	{
		if(m_pixAnim)
		{
			m_pixelImageOut->pixelUpdate(m_pixAnim->getPixels2());
		}
		else
		{
			m_pixelImageOut->pixelUpdate();
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

void Canvas::setCurrentAnimationProgress(const float &current_progress)
{
	m_currentAnimTime = current_progress * m_totalAnimTime;
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
	else if(m_animType == Canvas::AnimationType::PIX_ANIM && m_pixelImageIn && m_pixelImageOut)
	{
		m_pixelImageIn->pixelUpdate(m_pixAnim->getTexture1Frame(m_currentAnimTime));
		m_pixelImageOut->pixelUpdate(m_pixAnim->getTexture2Frame(m_currentAnimTime));
	}

	if(m_isAnimPlaying)
	{
		Program::requestUpdate();
	}
	else
	{
		Program::expireRequestUpdate();
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
	bool eI = false, sI = false;
	if(m_animType == Canvas::AnimationType::OBJ_ANIM)
	{
		if(m_endingImage)
		{
			eI = true;
		}
		if(m_startingImage)
		{
			sI = true;
		}
		if(m_startingImage->getVertexDepth(0) > m_endingImage->getVertexDepth(0))
		{
			if(sI)
			{
				m_startingImage->render(&m_plane);
			}
			if(eI)
			{
				m_endingImage->render(&m_plane);
			}
		}
		else
		{
			if(eI)
			{
				m_endingImage->render(&m_plane);
			}
			if(sI)
			{
				m_startingImage->render(&m_plane);
			}
		}
	}
	else if(m_animType == Canvas::AnimationType::PIX_ANIM && m_pixelImageIn && m_pixelImageOut)
	{
		m_pixelImageOut->render(&m_plane);
		m_pixelImageIn->render(&m_plane);
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

const float& Canvas::getTotalTime()
{
	return m_totalAnimTime;
}  
