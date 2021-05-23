#pragma once 

#include "AnimControlButton.h"


class NextFrameControl : public AnimControlButton
{

public:
    //default constructors and dectructors
	NextFrameControl();
	~NextFrameControl() = default;

	//named constructors
	static NextFrameControl* makeNextFrameButton(const sf::Vector2f &pos);
	static NextFrameControl* makePreviousFrameButton(const sf::Vector2f &pos);

	//render and update
	void render(sf::RenderTarget *target) override;
	void update(sf::Vector2i mousePos, sf::Event &event) override;

private:
	//private constructor
	NextFrameControl(const sf::Vector2f &pos);

};