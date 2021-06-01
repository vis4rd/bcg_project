#include "../../include/program/Program.h"

Program::Program()
{
    std::string title = "BCG - Testowy";
    sf::VideoMode window_bounds(1280, 720);
    window_bounds.bitsPerPixel = sf::VideoMode::getDesktopMode().bitsPerPixel;
    unsigned fps_limit = 60;
    bool vertical_sync_enabled = 0;

    m_window = new sf::RenderWindow(window_bounds, title, sf::Style::Close | sf::Style::Titlebar);
    m_window->setFramerateLimit(fps_limit);
    m_window->setVerticalSyncEnabled(vertical_sync_enabled);
    m_window->setKeyRepeatEnabled(false);
    


    timePanel = new PanelTimeline(sf::Vector2f(20.f, 620.f), sf::Vector2f(960.f, 90.f) );
    buttonPanel = new PanelButton(sf::Vector2f(980.f, 10.f), sf::Vector2f(290.f, 700.f));

}

Program::~Program()
{
    delete m_window;
    
    delete buttonPanel;
    delete timePanel;
}

void Program::endApp()
{
    std::cout << "Ending Application" << std::endl;
}

void Program::updateDeltaTime()
{
    /*Updates the deltaTime variable with the time it takes to update and render one frame*/
   m_deltaTime = m_dtClock.restart().asSeconds();
}

void Program::updateSFMLEvents()
{
    while(m_window->pollEvent(m_event))
    {
        switch(m_event.type)
        {
            case sf::Event::Closed:
            {
                m_window->close();
                break;
            }
            default: break;
        }//switch
        this->update(sf::Mouse::getPosition(*m_window), m_event);
    }//while
}

void Program::update(sf::Vector2i mousePos, sf::Event &event)
{    
    if(m_window->isOpen())
    {
        this->updateDeltaTime();

        //here there will be panels updated
        timePanel->update(mousePos, event);
        buttonPanel->update(mousePos, event);
    }
    else//Applications end
    {
        this->endApp();
    }
}

void Program::render()
{
   m_window->clear();

   //here there will be panels rendered
   timePanel->render(m_window);
   buttonPanel->render(m_window);
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
