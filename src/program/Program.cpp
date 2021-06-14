#include "../../include/program/Program.h"

bool Program::requestedUpdate = false;

Program::Program()
{
    std::string title = "BCG - SlidesAnimations";
    sf::VideoMode window_bounds(1280, 720);
    window_bounds.bitsPerPixel = sf::VideoMode::getDesktopMode().bitsPerPixel;
    unsigned fps_limit = 60;
    bool vertical_sync_enabled = 0;

    m_window = new sf::RenderWindow(window_bounds, title, sf::Style::Close | sf::Style::Titlebar);
    m_window->setFramerateLimit(fps_limit);
    m_window->setVerticalSyncEnabled(vertical_sync_enabled);
    m_window->setKeyRepeatEnabled(false);
    
    m_timePanel = new PanelTimeline(sf::Vector2f(10.f, 10.f), sf::Vector2f(960.f, 700.f) );
    m_buttonPanel = new PanelButton(sf::Vector2f(980.f, 10.f), sf::Vector2f(290.f, 700.f));

    m_timePanel->getCanvas()->setStartingImage("../res/images/example1.jpg");
    m_timePanel->getCanvas()->setEndingImage("../res/images/example2.jpg");
    m_timePanel->getCanvas()->setAnimation(std::make_unique<DimmingAnimation>());
    m_timePanel->getTimeline()->setTotalTime(1.f);
    m_timePanel->getTimeline()->setFrames(15);
    m_timePanel->getCanvas()->setTotalAnimationTime( m_timePanel->getTimeline()->getTotalTime() );

    Settings* sets = Settings::getInstance();
    sets->setPath1("../res/images/example1.jpg");
    sets->setPath2("../res/images/example2.jpg");
    sets->setCurrentAnim(1u);
    sets->setCurrentFrames(1);
}

Program::~Program()
{
    delete m_window;
    delete m_timePanel;
    delete m_buttonPanel;
}

void Program::endApp()
{
    std::cout << "Ending Application" << std::endl;
}

void Program::setAnimationFromSettings(Settings* settings)
{
    switch( settings->getCurrentAnim() )
    {
        case(1u):
        {
            m_timePanel->getCanvas()->setAnimation( std::make_unique<DimmingAnimation>() );
            break;
        }
        case(2u):
        {
            m_timePanel->getCanvas()->setAnimation( std::make_unique<AlfaAnimation>() );
            break;
        }
        case(3u):
        {
            m_timePanel->getCanvas()->setAnimation( std::make_unique<ByBrightnessAnimation>() );
            break;
        }
        case(4u):
        {
            m_timePanel->getCanvas()->setAnimation( std::make_unique<SlideAnimation>() );
            break;
        }
        case(5u):
        {
            m_timePanel->getCanvas()->setAnimation( std::make_unique<ScaleAnimation>() );
            break;
        }
        case(6u):
        {
            m_timePanel->getCanvas()->setAnimation( std::make_unique<RingAnimation>() );
            break;
        }
        case(7u):
        {
            m_timePanel->getCanvas()->setAnimation( std::make_unique<FlyAnimation>() );
            break;
        }
        default:
        {
            break;
        }
    }
    m_timePanel->getCanvas()->setTotalAnimationTime( m_timePanel->getTimeline()->getTotalTime() );
    m_buttonPanel->getAnimationChoice()->changeRead();
}

void Program::setFramesFromSettings(Settings* settings)
{
    switch ( settings->getCurrentFrames() )
    {
         case(1u):
        {
            m_timePanel->getTimeline()->setFrames( 15u );
            break;
        }
        case(2u):
        {
            m_timePanel->getTimeline()->setFrames( 30u );
            break;
        }
        case(3u):
        {
            m_timePanel->getTimeline()->setFrames( 60u );
            break;
        }
        case(4u):
        {
            m_timePanel->getTimeline()->setFrames( 120u );
            break;
        }

        default:
        {
            char* input = tinyfd_inputBox ( "Frames Choice", "Frames amount?" , "10" );
            if(input)
            {
                int frames = std::stoi(input);
                if (frames > 500)
                {
                    m_timePanel->getTimeline()->setFrames( 500u );
                    settings->setCurrentFrames( 500u );

                }

                else if(frames < 10)
                {
                    m_timePanel->getTimeline()->setFrames( 10u );
                    settings->setCurrentFrames( 10u );
                }

                else
                {
                    m_timePanel->getTimeline()->setFrames( static_cast<short>(frames) );
                    settings->setCurrentFrames( 10u );
                }
                break;
            }
            else
            {
                m_timePanel->getTimeline()->setFrames( 10u );
                settings->setCurrentFrames( static_cast<short>(10u) );
            }
        }

    }
    m_timePanel->getCanvas()->setTotalAnimationTime( m_timePanel->getTimeline()->getTotalTime() );
    m_buttonPanel->getFramesChoice()->changeRead();
}



void Program::requestUpdate()
{
    requestedUpdate = true;
}

void Program::expireRequestUpdate()
{
    requestedUpdate = false;
}

void Program::updateDeltaTime()
{
    /*Updates the deltaTime variable with the time it takes to update and render one frame*/
   m_deltaTime = m_dtClock.restart().asSeconds();
}

void Program::saveSequence(sf::Vector2i mousePos, sf::Event &event)
{
    m_timePanel->getTimeline()->setCurrentTime(0.f);

    std::string name;
    time_t now = time(0);
    char* date = ctime(&now);
    std::string dir(date);
    std::replace( dir.begin(), dir.end(), ' ', '_');
    std::replace( dir.begin(), dir.end(), ':', '-');
    dir.pop_back();
    std::filesystem::create_directory(dir);

    int amount = static_cast<int> (m_timePanel->getTimeline()->getFrames());
    for (int i = 1; i <= amount; ++i)
    {
        name = "";  
        if(i>99)
        {
            name += std::to_string(i); 
        }
        else if(i>9)
        {
            name += "0" + std::to_string(i);
        }
        else
        {
            name += "00" + std::to_string(i);
        }

        m_timePanel->update(mousePos,event,m_deltaTime);
        m_timePanel->getCanvas()->render(m_window);
        m_timePanel->getCanvas()->getPlane().getTexture().copyToImage().saveToFile(dir+"/"+name+".bmp");
        m_timePanel->getTimeline()->skipNextFrame();
    }

    m_timePanel->getTimeline()->setCurrentTime(0.f);
    m_timePanel->update(mousePos, event, m_deltaTime);
    m_timePanel->render(m_window);
    tinyfd_messageBox("Message", "The animation has been saved!", "ok", "info", 1);
}


void Program::updateSFMLEvents()
{
    this->updateDeltaTime();
    if(m_window->pollEvent(m_event))
    {
        switch(m_event.type)
        {
            case sf::Event::Closed:
            {
                m_window->close();
                break;
            }
            default: 
            {
                this->update(sf::Mouse::getPosition(*m_window), m_event);
                break;
            }
        }//switch
    }
    else if(requestedUpdate)
    {
        m_event = sf::Event();
        this->update(sf::Mouse::getPosition(*m_window), m_event);
    }
}

void Program::update(sf::Vector2i mousePos, sf::Event &event)
{    
    Settings* sets = Settings::getInstance();

    if(m_window->isOpen())
    {
        m_timePanel->update(mousePos, event, m_deltaTime );
        m_buttonPanel->update(mousePos, event);
    }
    else//Applications end
    {
        this->endApp();
    }

    if( m_buttonPanel->getImageUp()->isChanged() )
    {
        sets->setPath1( m_buttonPanel->getImageUp()->getPath() );
        //std::cout << sets->getPath1() <<std::endl;
        m_timePanel->getCanvas()->setStartingImage( sets->getPath1() );
        this->setAnimationFromSettings(sets);
        m_buttonPanel->getImageUp()->changeRead();
    }

    if ( m_buttonPanel->getImageDown()->isChanged() )
    {
        sets->setPath2( m_buttonPanel->getImageDown()->getPath() );
        //std::cout << sets->getPath2() <<std::endl;
        m_timePanel->getCanvas()->setEndingImage( sets->getPath2() );
        this->setAnimationFromSettings(sets);
        m_buttonPanel->getImageDown()->changeRead();
    }

    if ( m_buttonPanel->getAnimationChoice()->isChanged() )
    {
        sets->setCurrentAnim( m_buttonPanel->getAnimationChoice()->getCurrentChoice() );
        this->setAnimationFromSettings(sets);
    }

    if ( m_buttonPanel->getFramesChoice()->isChanged() )
    {
        sets->setCurrentFrames( m_buttonPanel->getFramesChoice()->getCurrentChoice() );
        this->setFramesFromSettings(sets);
    }

    if (m_buttonPanel->getSaveButton()->isPressed() )
    {
        this->saveSequence(mousePos, event);
    }
}

void Program::render()
{
   m_window->clear();

   m_timePanel->render(m_window);
   m_buttonPanel->render(m_window);

   m_window->display();
}

void Program::run()
{
    while(m_window->isOpen())
    {
       this->updateSFMLEvents();
       this->render();
    }
}
