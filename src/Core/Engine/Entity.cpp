#include <Engine/Entity.h>
#include <Assert.h>
Entity::Entity()
    : m_body         (0)
    , m_physics      (0)
    , m_view         (0)
    , m_gamepad      (0)
    , m_isAlive      (true)
{}

Entity::~Entity(){}

void Entity::update(){}

Body*                Entity::body()          const{ return m_body          ;}
View*                Entity::view()          const{ return m_view          ;}
Physics*             Entity::physics()       const{ return m_physics       ;}
GamePad*             Entity::gamepad()       const{ return m_gamepad       ;}

void Entity::setBody   (Body*    body   )         { m_body    = body   ; }
void Entity::setPhysics(Physics* physics)         { m_physics = physics; }
void Entity::setView   (View*    view   )         { m_view    = view   ; }
void Entity::setGamepad(GamePad* gamepad)         { m_gamepad = gamepad; }

bool Entity::isAlive(){ return m_isAlive; }

void Entity::destroyThis()
{
    ASSERT(m_isAlive);
    if(m_isAlive)
    {
	destroyed(this);
	m_isAlive=false;
    }
}




