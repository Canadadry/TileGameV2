#include "Screen.h"
#include <SFML/Graphics.hpp>

Screen*           Screen::m_current = 0;
sf::RenderWindow* Screen::m_window = 0;

Screen::Screen()
: myScreenIsFinished(false)
, myNextScreen(0)
{	
}

Screen::~Screen()
{	
}

Screen* Screen::current()
{
	return m_current;
}

sf::RenderWindow* Screen::window()
{
	return m_window;
}


void Screen::display(sf::RenderTarget* screen_surface)
{
	render(screen_surface);
}

void Screen::setNextScreen(Screen *nextScreen) 
{
	myScreenIsFinished = true;
	myNextScreen = nextScreen;
	myNextScreen->entering();
}


Screen * Screen::getNextScreen(void) 
{
	myScreenIsFinished = false;
	return myNextScreen;
}


bool Screen::isScreenFinished(void) 
{
	return myScreenIsFinished;
}

void Screen::mainLoop(Screen* first_screen, std::string gameName ,int window_width, int window_height)
{
	m_window = new sf::RenderWindow(sf::VideoMode(window_width, window_height), gameName,sf::Style::Titlebar | sf::Style::Close);
	m_window->setVerticalSyncEnabled(true);
	m_window->setKeyRepeatEnabled(false);
	sf::Clock clock;
	bool hasFocus = true;

	m_current = first_screen;
	first_screen->entering();

	int elapsedTimeMS = 0;
	while (m_window->isOpen() && m_current != 0)
	{
		sf::Event event;
		while (m_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window->close();
			}
			else if(event.type == sf::Event::GainedFocus)
			{
				hasFocus = true;
			}
			else if(event.type == sf::Event::LostFocus)
			{
				hasFocus = false;
			}
			else
			{
				if(hasFocus)
				{
					m_current->handleEvent(event);
				}
			}
		}
		if(elapsedTimeMS >0)
		{
			if(hasFocus)
			{
				m_current->update(elapsedTimeMS);
			}
		}

		m_window->setActive(true);
		m_window->clear(sf::Color::Black);
		m_current->display(m_window);
		m_window->display();
		elapsedTimeMS = clock.restart().asMilliseconds();

		if(m_current->isScreenFinished())
		{
			m_current = m_current->getNextScreen();
		}

	}

}

