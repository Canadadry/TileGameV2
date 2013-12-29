#include <Engine/Game.h>
#include <Engine/Entity.h>
#include <Engine/View.h>
#include <Engine/GamePad.h>
#include <Engine/Physics.h>
#include <Engine/Body.h>

#include <SFML/Window/Event.hpp>

#include <algorithm>

typedef  std::list<GamePad*>::iterator GamePad_it;
typedef  std::list<View*>::iterator View_it;
typedef  std::list<Entity*>::iterator Entity_it;
typedef  std::list<Physics*>::iterator Physic_it;
typedef  std::list<Body*>::iterator Body_it;
typedef  std::list<Body*>::const_iterator ConstBody_it;

Game::Game(int window_width,int window_height)
    : m_entities()
    , m_window_width(window_width)
    , m_window_height(window_height)
{
}

Game::~Game()
{
    for(Entity_it it = m_entities.begin(); it != m_entities.end();it++)
    {
	destroyedEntity(*it);
    }
}

void Game::addEntity(Entity* entity)
{
    Entity_it findIter = std::find(m_entities.begin(), m_entities.end(), entity);
    if(findIter != m_entities.end())
    {
	printf("entity (%s) already added!!!\n",entity->name.c_str());
	return;
    }
    entityAdded(entity);
    entity->game = this;
    entity->entityCreated.Connect(this,&Game::addEntity);
    entity->destroyed.Connect(this,&Game::onEntityDestroyed);
    m_entities.push_back(entity);
    if(entity->view())
    {
	m_views.push_front(entity->view());
    }
    if(entity->gamepad())
    {
	m_gamepads.push_front(entity->gamepad());
    }
    if(entity->physics())
    {
	m_physics.push_front(entity->physics());
    }
    if(entity->body())
    {
	m_bodies.push_back(entity->body());
	//		m_world.addBody(entity->body());
    }
}

void Game::onEntityDestroyed(Entity* entity)
{
    Entity_it findIter = std::find(m_entities_to_destroyed.begin(), m_entities_to_destroyed.end(), entity);

    if(findIter != m_entities_to_destroyed.end())
    {
	printf("entity(%s) already register to be destroyed!!!\n",entity->name.c_str());
	return;
    }
    entityRemoved(entity);
    m_entities_to_destroyed.push_back(entity);
}

void Game::clear()
{
    for(Entity_it it = m_entities.begin(); it != m_entities.end();it++)
    {
	onEntityDestroyed(*it);
    }
}

void Game::destroyedEntity(Entity* entity)
{
    Entity_it findIter = std::find(m_entities_to_destroyed.begin(), m_entities_to_destroyed.end(), entity);

    if(findIter != m_entities_to_destroyed.end())
    {
	m_entities.remove(entity);
	if(entity->view())
	{
	    m_views.remove(entity->view());
	}
	if(entity->gamepad())
	{
	    m_gamepads.remove(entity->gamepad());
	}
	if(entity->physics())
	{
	    m_physics.remove(entity->physics());
	}
	if(entity->body())
	{
	    m_bodies.remove(entity->body());
	    //			m_world.removeBody(entity->body());
	}


	delete entity;
    }
}


void Game::handleEvent(const sf::Event& Event)
{
    for(GamePad_it it = m_gamepads.begin(); it != m_gamepads.end();it++)
    {
	(*it)->handleEvent(Event);
    }
}

void Game::render(sf::RenderTarget* screen_surface)
{
    for(View_it it = m_views.begin(); it != m_views.end();it++)
    {
	(*it)->update();
	(*it)->render(*screen_surface);
    }
}

void Game::update()
{
    for(GamePad_it it = m_gamepads.begin(); it != m_gamepads.end();it++)
    {
	(*it)->update();
    }
    for(Physic_it it = m_physics.begin(); it != m_physics.end();it++)
    {
	(*it)->update();
    }

    checkCollision();

    for(Entity_it it = m_entities.begin(); it != m_entities.end();it++)
    {
	(*it)->update();
    }
    for(Entity_it it = m_entities_to_destroyed.begin(); it != m_entities_to_destroyed.end();it++)
    {
	destroyedEntity(*it);
    }
    m_entities_to_destroyed.clear();
}

void Game::checkCollision()
{
    for(Body_it it1 = m_bodies.begin(); it1 != m_bodies.end();it1++)
    {
	for(Body_it it2 = m_bodies.begin(); it2 != m_bodies.end();it2++)
	{
	    Body* b1 = *it1;
	    Body* b2 = *it2;

	    if(b1 != b2)
	    {
		bool b1intersted = ((b1->collisionMask & b2->collideCategory) == b2->collideCategory);
		bool b2intersted = ((b2->collisionMask & b1->collideCategory) == b1->collideCategory);
		if(b1intersted || b2intersted )
		{
		    if(b1->intersects(*b2))
		    {
			if(b1intersted) b1->collideWidth(b2);
			if(b2intersted) b2->collideWidth(b1);
		    }
		}
	    }
	}
    }

}

int Game::windowHeight() const
{
    return m_window_height;
}

int Game::windowWidth() const
{
    return m_window_width;
}




