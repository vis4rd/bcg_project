#pragma once

#include "../gui/Object.h"

class Program
{
public:
	Program();
	~Program();

	void endApp();

	void updateDeltaTime();
	void updateSFMLEvents();
	void update();

	void render();

	void run();

private:
	sf::RenderWindow *m_window;
	sf::Event m_event;

	sf::Clock m_dtClock;
	float m_deltaTime;
};
