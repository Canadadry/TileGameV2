#ifndef GAMEPAD_H_
#define GAMEPAD_H_

#include <Engine/Component.h>

class Entity;

namespace sf{ class Event; };

class GamePad : public Component
{
public:
	explicit GamePad(Entity& entity);
	virtual ~GamePad();

	virtual void handleEvent(const sf::Event& Event) =0;

};

#endif /* GAMEPAD_H_ */
