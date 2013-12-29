#include <Engine/Entity.h>
#include <Engine/Physics.h>
#include <Engine/Body.h>
#include <Assert.h>


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
    entity.body()->setPosition(entity.body()->position()+speed/* *dt*/);
}
