#include "../../include/gui/Canvas.h"
#include "../../include/program/Program.h"

Canvas::Canvas()
:
m_plane(std::make_shared<sf::RenderTexture>()),
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
	m_plane->create(1.f, 1.f);
}

Canvas::Canvas(const sf::Vector2f &position, const sf::Vector2f &size)
:
m_plane(std::make_shared<sf::RenderTexture>()),
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
	m_plane->create(size.x, size.y);
	m_planeBody.setPosition(position);
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
	m_startingImage = std::make_unique<AnimatedImage>(
			sf::Vector3f(m_plane->getSize().x/2.f, m_plane->getSize().y/2.f, 0.f),
			std::move(tex),
			static_cast<sf::Vector2f>(m_plane->getSize())
			);
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
	m_endingImage = std::make_unique<AnimatedImage>(
			sf::Vector3f(m_plane->getSize().x/2.f, m_plane->getSize().y/2.f, 0.f),
			std::move(tex),
			static_cast<sf::Vector2f>(m_plane->getSize())
			);
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
	if(current_time >= 0.f)
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
	m_plane->clear();
	m_plane->create(new_size.x, new_size.y);
}

void Canvas::setPosition(const sf::Vector2f &new_position)
{
	m_planeBody.setPosition(new_position);
}


sf::RenderTexture& Canvas::getPlane()
{
	return *m_plane;
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

void Canvas::render(std::shared_ptr<sf::RenderTarget> target)
{
	m_plane->clear();

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
		float depthSI = ( m_startingImage->getVertexDepth(0)
						+ m_startingImage->getVertexDepth(1)
						+ m_startingImage->getVertexDepth(2)
						+ m_startingImage->getVertexDepth(3)) / 4.f;
		float depthEI = ( m_endingImage->getVertexDepth(0)
						+ m_endingImage->getVertexDepth(1)
						+ m_endingImage->getVertexDepth(2)
						+ m_endingImage->getVertexDepth(3)) / 4.f;
		if(depthSI > depthEI)
		{
			if(sI && !(depthSI < 0.f))
			{
				m_startingImage->render(m_plane);
			}
			if(eI && !(depthEI < 0.f))
			{
				m_endingImage->render(m_plane);
			}
		}
		else
		{
			if(eI && !(depthEI < 0.f))
			{
				m_endingImage->render(m_plane);
			}
			if(sI && !(depthSI < 0.f))
			{
				m_startingImage->render(m_plane);
			}
		}
	}
	else if(m_animType == Canvas::AnimationType::PIX_ANIM && m_pixelImageIn && m_pixelImageOut)
	{
		m_pixelImageOut->render(m_plane);
		m_pixelImageIn->render(m_plane);
	}

	m_plane->display();
	m_planeBody.setTexture(m_plane->getTexture(), true);
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
