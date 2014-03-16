#include <Engine/Entity.h>
#include <Debug/Assert.h>
#include <Engine/Body.h>
#include <Engine/Physics.h>
#include <Engine/View.h>
#include <Engine/GamePad.h>

Entity::Entity()
    : m_body         (0)
    , m_physics      (0)
    , m_view         (0)
    , m_gamepad      (0)
    , m_isAlive      (true)
{}

Entity::~Entity()
{
    if(m_body    != NULL) delete m_body;
    if(m_view    != NULL) delete m_view;
    if(m_physics != NULL) delete m_physics;
    if(m_gamepad != NULL) delete m_gamepad;
}

void Entity::update(){}

Body*                Entity::body()          const{ return m_body          ;}
View*                Entity::view()          const{ return m_view          ;}
Physics*             Entity::physics()       const{ return m_physics       ;}
GamePad*             Entity::gamepad()       const{ return m_gamepad       ;}

void Entity::setBody   (Body*    body   )         { m_body    = body   ; ((Component*)m_body)->m_entity    = this; }
void Entity::setPhysics(Physics* physics)         { m_physics = physics; m_physics->m_entity = this; }
void Entity::setView   (View*    view   )         { m_view    = view   ; m_view->m_entity    = this; }
void Entity::setGamepad(GamePad* gamepad)         { m_gamepad = gamepad; m_gamepad->m_entity = this; }

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




