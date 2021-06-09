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
    
    m_timePanel = new PanelTimeline(sf::Vector2f(10.f, 10.f), sf::Vector2f(960.f, 680.f) );
    m_buttonPanel = new PanelButton(sf::Vector2f(980.f, 10.f), sf::Vector2f(290.f, 700.f));

    m_timePanel->getCanvas()->setStartingImage("../res/images/example1.jpg");
    m_timePanel->getCanvas()->setEndingImage("../res/images/example2.jpg");
    m_timePanel->getCanvas()->setAnimation(std::make_unique<DimmingAnimation>());
    m_timePanel->getTimeline()->setTotalTime(10.f);
    m_timePanel->getCanvas()->setTotalAnimationTime( m_timePanel->getTimeline()->getTotalTime() );

    Settings* sets = Settings::getInstance();
    sets->setPath1("../res/images/example1.jpg");
    sets->setPath2("../res/images/example2.jpg");
    sets->setCurrentAnim(1u);
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
            break;}
        case(2u):
        {
            m_timePanel->getCanvas()->setAnimation( std::make_unique<AlfaAnimation>() );
            break;}
        case(3u):
        {
            m_timePanel->getCanvas()->setAnimation( std::make_unique<ByBrightnessAnimation>() );
            break;}
        case(4u):
        {
            m_timePanel->getCanvas()->setAnimation( std::make_unique<SlideAnimation>() );
            break;}
        case(5u):
        {
            m_timePanel->getCanvas()->setAnimation( std::make_unique<ScaleAnimation>() );
            break;}
        case(6u):
        {
            m_timePanel->getCanvas()->setAnimation( std::make_unique<RingAnimation>() );
            break;}
    }
    //m_timePanel->getTimeline()->setTotalTime(10.f);
    m_timePanel->getCanvas()->setTotalAnimationTime( m_timePanel->getTimeline()->getTotalTime() );
    m_buttonPanel->getAnimationChoice()->changeRead();
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
    if(m_window->isOpen())
    {
        m_timePanel->update(mousePos, event, m_deltaTime);
        m_buttonPanel->update(mousePos, event);
    }
    else//Applications end
    {
        this->endApp();
    }

    Settings* sets = Settings::getInstance();

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
