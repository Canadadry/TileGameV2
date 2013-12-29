#include "Body.h"
#include <cmath>

Body::Body(Entity& entity)
    : Component(entity)
    , m_aabb(0.0,0.0,0.0,0.0)
    , m_origin(0.0,0.0)
    , m_computedPosition(0.0,0.0)
{
}

Body::~Body()
{
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
