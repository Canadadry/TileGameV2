/*
 * Physics.cpp
 *
 * Asteroid - Copyright (c) 12 févr. 2013 - Jerome Mourey
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
 *  Created on: 12 févr. 2013
 */

#include "Physics.h"

#include <Engine/Entity.h>
#include <Engine/Body.h>
#include <cmath>
#include <Engine/World.h>

Physics::Physics(Entity* entity)
: m_entity (entity)
, m_speed (0.0,0.0)
{
}

Physics::~Physics()
{
}

void  Physics::update(World& world)
{

	updatedSpeed();
//	printf("new speed %f,%f\n",m_speed.x,m_speed.y);

	//moving body if it's possible
	sf::Vector2f old_pos = m_entity->body()->position();
	sf::Vector2f delta   = m_speed;//sf::Vector2f(velocityX  ,velocityY);

	sf::Vector2f deltaX  = sf::Vector2f(m_speed.x  ,0);
	sf::Vector2f deltaY  = sf::Vector2f(0          ,m_speed.y);
	sf::Vector2f deltaX2 = sf::Vector2f(m_speed.x/2  ,0);
	sf::Vector2f deltaY2 = sf::Vector2f(0          ,m_speed.y/2);
	sf::Vector2f deltaX4 = sf::Vector2f(m_speed.x/4  ,0);
	sf::Vector2f deltaY4 = sf::Vector2f(0          ,m_speed.y/4);
	sf::Vector2f deltaX8 = sf::Vector2f(m_speed.x/8  ,0);
	sf::Vector2f deltaY8 = sf::Vector2f(0          ,m_speed.y/8);

	sf::Vector2f finalDelta = sf::Vector2f(0,0);

	m_entity->body()->setPosition(old_pos + delta);

	if(world.isCollidingTerrain(m_entity->body()))
	{
		m_entity->body()->setPosition(old_pos+deltaX);
		finalDelta.x = deltaX.x;
		if(world.isCollidingTerrain(m_entity->body()))
		{

			finalDelta.x = deltaX2.x;
			m_entity->body()->setPosition(old_pos+deltaX2);
			if(world.isCollidingTerrain(m_entity->body()))
			{

				finalDelta.x = deltaX4.x;
				m_entity->body()->setPosition(old_pos+deltaX4);
				if(world.isCollidingTerrain(m_entity->body()))
				{
					finalDelta.x = deltaX8.x;
					m_entity->body()->setPosition(old_pos+deltaX8);
					if(world.isCollidingTerrain(m_entity->body()))
					{
						finalDelta.x = 0;
						m_entity->body()->setPosition(old_pos);
					}				}
			}
			m_speed.x = 0;
		}

		m_entity->body()->setPosition(old_pos+deltaY);
		finalDelta.y = deltaY.y;
		if(world.isCollidingTerrain(m_entity->body()))
		{

			finalDelta.y = deltaY2.y;
			m_entity->body()->setPosition(old_pos+deltaY2);
			if(world.isCollidingTerrain(m_entity->body()))
			{

				finalDelta.y = deltaY4.y;
				m_entity->body()->setPosition(old_pos+deltaY4);
				if(world.isCollidingTerrain(m_entity->body()))
				{
					finalDelta.y = deltaY8.y;
					m_entity->body()->setPosition(old_pos+deltaY8);
					if(world.isCollidingTerrain(m_entity->body()))
					{
						finalDelta.y = 0;
						m_entity->body()->setPosition(old_pos);
					}				}
			}
			m_speed.y = 0;
		}
		m_entity->body()->setPosition(old_pos+finalDelta);

	}
}
