#include "Body.h"
#include <cmath>
#include <algorithm>
#include <Engine/Entity.h>

typedef  std::list<Contact>::iterator Contact_it;

Body::Body()
    : Component()
    , m_aabb(0.0,0.0,0.0,0.0)
    , m_origin(0.0,0.0)
    , m_computedPosition(0.0,0.0)
    , collideCategory(0)
    , collisionMask(0)
{
}

Body::~Body()
{
    for(Contact_it it = m_contactVector.begin(); it != m_contactVector.end();it++)
    {
	(*it).body->clearContactWith(this);
    }

}

void Body::move(float x, float y)
{
    setPosition(position()+sf::Vector2f(x,y));
}

sf::Vector2f Body::size() const
{
    return sf::Vector2f(m_aabb.width,m_aabb.height);
}

void Body::setOrigin(sf::Vector2f origin)
{
    sf::Vector2f pos = position();
    m_origin = origin;
    setPosition(pos);
}

void Body::setPosition(sf::Vector2f position)
{
    m_aabb.left = position.x - m_origin.x;
    m_aabb.top  = position.y - m_origin.y;

    m_computedPosition = position;
}

void Body::setSize(sf::Vector2f size)
{
    m_aabb.width = size.x;
    m_aabb.height = size.y;
}

sf::Vector2f Body::position() const
{
    return m_computedPosition;
}

sf::Vector2f Body::origin() const
{
    return m_origin;
}

bool Body::intersects(const Body& body)const
{
    sf::FloatRect intersection;
    return m_aabb.intersects(body.m_aabb,intersection);
}


void Body::updateCollision(Body& body)
{
    for(Contact_it it = m_contactVector.begin(); it != m_contactVector.end();it++)
    {
	if((*it).body == &body)
	{
	    (*it).valid = true;
	    return;
	}
    }
    Contact contact;
    contact.thisBody = this;
    contact.body = &body;
    contact.valid = true;
    m_contactVector.push_back(contact);
    beginCollideWidth(&body);


}

void Body::update()
{
    for(Contact_it it = m_contactVector.begin(); it != m_contactVector.end();it++)
    {
	(*it).valid = false;
    }
}

void Body::updateCollideList()
{
    for(Contact_it it = m_contactVector.begin(); it != m_contactVector.end();it++)
    {
	if(!(*it).valid)
	{
	    (*it).body->endCollideWidth((*it).thisBody);
	    m_contactVector.erase(it);
	    break;
	}
    }
}

void Body::clearContactWith(Body* body)
{
    for(Contact_it it = m_contactVector.begin(); it != m_contactVector.end();it++)
    {
	if((*it).body == body)
	{
	    m_contactVector.erase(it);
	    break;
	}
    }
}
