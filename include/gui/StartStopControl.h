#pragma once

#include "AnimControlButton.h"

class StartStopControl : public AnimControlButton
{

public:

    // constructors and destructors
	StartStopControl(); 
	StartStopControl(const sf::Vector2f &pos);
	~StartStopControl() = default;

	// update methods	
	void update(sf::Vector2i mousePos, sf::Event &event) override;
    void render(sf::RenderTarget *target) override;

    //getter
    bool isPlay() const;

    //control buttons
    void play();
    void pause();
    void ON_OFF();

private:
	bool m_isPlay = false;

};