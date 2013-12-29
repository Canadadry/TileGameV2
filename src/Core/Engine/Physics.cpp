#include <Engine/Entity.h>
#include <Engine/Physics.h>
#include <Engine/Body.h>
#include <Debug/Assert.h>

#include <cmath>

Physics::Physics(Entity& entity)
: Component (entity)
, gravity(0.0,0.0)
, speed (0.0,0.0)
{
}

Physics::~Physics()
{
}

void  Physics::update()
{
    ASSERT(entity.body());
    lastPos = entity.body()->position();
    speed += gravity /* * dt*/;
    sf::Vector2f pos = entity.body()->position();
    pos += speed /* *dt */;
    pos.x = roundf(pos.x);
    pos.y = roundf(pos.y);

    entity.body()->setPosition(pos);
}
