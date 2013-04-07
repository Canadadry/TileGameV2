/*
 * Body.cpp
 *
 * Asteroid - Copyright (c) 12 f�vr. 2013 - Jerome Mourey
 *
 * This software is provided 'as-is', without any express or
 * implied warranty. In no event will the authors be held
 * liable for any damages arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute
 * it freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented;
 *    you must not claim that you wrote the original software.
 *    If you use this software in a product, an acknowledgment
 *    in the product documentation would be appreciated but
 *    is not required.
 * 
 * 2. Altered source versions must be plainly marked as such,
 *    and must not be misrepresented as being the original software.
 * 
 * 3. This notice may not be removed or altered from any
 *    source distribution.
 *
 *  Created on: 12 f�vr. 2013
 */

#include "Body.h"
#include <cmath>

Body::Body(Entity* entity)
: type    (0)
, collisionHandler(0)
, isAABBCornerFree()
, m_entity(entity)
, m_aabb(0.0,0.0,0.0,0.0)
, m_origin(0.0,0.0)
, m_computedPosition(0.0,0.0)
{
}

Body::~Body()
{
}

sf::Vector2f Body::size() const
{
	return sf::Vector2f(m_aabb.width,m_aabb.height);
}

Entity* Body::entity()
{
	return m_entity;
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

bool Body::intersects(const Body& body)const
{
	sf::FloatRect intersection;
	return m_aabb.intersects(body.m_aabb,intersection);
}




bool Body::handleCollision(Body* body)
{
	bool ret = true;
	if(collisionHandler)
	{
		ret = collisionHandler->HandleCollision(body);
	}
	return ret;
}

bool Body::touchingWall()
{
	return  (  ( isAABBCornerFree[Body::BottomLeft ] && isAABBCornerFree[Body::TopLeft ])
	        || ( isAABBCornerFree[Body::BottomRight] && isAABBCornerFree[Body::TopRight]));
}

bool Body::isOnFloor()
{
	return  (   isAABBCornerFree[Body::BottomLeft ]
	        &&  isAABBCornerFree[Body::BottomRight]);
}




