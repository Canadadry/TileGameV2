#include "Screen.h"
#include <SFML/Graphics.hpp>

Screen::Screen()
: myScreenIsFinished(false)
, myNextScreen(0)
{	
}

Screen::~Screen()
{	
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
	sf::RenderWindow window(sf::VideoMode(window_width, window_height), gameName,sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	window.setKeyRepeatEnabled(false);
	sf::Clock clock;
	bool hasFocus = true;

	Screen* currentScreen = first_screen;

	int elapsedTimeMS = 0;
	while (window.isOpen() && currentScreen != 0)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
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
					currentScreen->handleEvent(event);
				}
			}
		}
		if(elapsedTimeMS >0)
		{
			if(hasFocus)
			{
				currentScreen->update(elapsedTimeMS);
			}
		}

		window.setActive(true);
		window.clear(sf::Color::Black);
		currentScreen->display(&window);
		window.display();
		elapsedTimeMS = clock.restart().asMilliseconds();

		if(currentScreen->isScreenFinished())
		{
			currentScreen = currentScreen->getNextScreen();
		}

	}

}

