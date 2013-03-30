#ifndef _SCREEN_
#define _SCREEN_

#include <string>

namespace sf{
	class RenderWindow;
class RenderTarget;
class Event;
}


class Screen {

public:

	virtual ~Screen();
	static void mainLoop(Screen* first_screen,std::string gameName = "MyFabulousGame",int window_width = 800,int window_height = 600);
	static Screen* current();
	static sf::RenderWindow* window();


protected:

	Screen();
	void setNextScreen(Screen *nextScreen);
	bool isScreenFinished();
	Screen *getNextScreen();

	virtual void entering() {}
	virtual void handleEvent(const sf::Event& Event) = 0;
    virtual void update(int elapsedTimeMS) =0;
	virtual void render(sf::RenderTarget* screen_surface) = 0;
	void display(sf::RenderTarget* screen_surface);

private:

	static Screen* m_current;
	static sf::RenderWindow* m_window;
	bool myScreenIsFinished;
	Screen *myNextScreen;




};

#endif
