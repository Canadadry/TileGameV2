
#ifndef KEYBOARDGAMEPAD_H_
#define KEYBOARDGAMEPAD_H_

#include <Engine/GamePad.h>

class KeyBoardGamePad : public GamePad
{
public:
	KeyBoardGamePad(Entity& entity);
	virtual ~KeyBoardGamePad();

	virtual void handleEvent(const sf::Event& Event);
	virtual void update();

};

#endif /* KEYBOARDGAMEPAD_H_ */
