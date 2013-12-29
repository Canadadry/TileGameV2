#ifndef PHYSICS_H_
#define PHYSICS_H_

#include <SFML/System/Vector2.hpp>
#include <Engine/Component.h>

class Entity;
class World;
class Body;


class Physics : public Component
{
public:
    explicit Physics(Entity& entity);
    virtual ~Physics();
    virtual void  update();

    sf::Vector2f gravity;
    sf::Vector2f speed;
    sf::Vector2f lastPos;

};

#endif /* PHYSICS_H_ */
