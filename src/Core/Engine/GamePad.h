#ifndef GAMEPAD_H_
#define GAMEPAD_H_

#include <Engine/Component.h>

class Entity;
class JSONValue;

namespace sf{ class Event; }

class GamePad : public Component
{
public:
    explicit GamePad(Entity& entity);
    virtual ~GamePad();

    virtual void handleEvent(const sf::Event& Event);

    static Component* build(Entity* entity,JSONValue& param);

};

#endif /* GAMEPAD_H_ */
