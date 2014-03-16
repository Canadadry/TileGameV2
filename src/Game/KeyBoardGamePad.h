
#ifndef KEYBOARDGAMEPAD_H_
#define KEYBOARDGAMEPAD_H_

#include <Engine/GamePad.h>

class KeyBoardGamePad : public GamePad
{
public:
	KeyBoardGamePad();
	virtual ~KeyBoardGamePad();

	virtual void handleEvent(const sf::Event& Event);
	virtual void update();

};

#endif /* KEYBOARDGAMEPAD_H_ */
