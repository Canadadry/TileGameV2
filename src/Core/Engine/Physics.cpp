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
#include <Engine/Force.h>

typedef  std::list<Force*>::iterator Force_it;



Physics::Physics(Entity* entity)
:drag     (0.0)
,velocityX(0.0)
,velocityY(0.0)
,m_entity (entity)
,m_friction(new Friction)
{
	forces.push_back(m_friction);
}

Physics::~Physics()
{
}

void  Physics::update(World& world)
{
	// apply forces

	const float max_speed = 3.0f; // pixel per cycle (16ms)
	const float max_force = 10.0f; // pixel per cycle per cycle (16ms)

	forceX = 0;
	forceY = 0;

//	printf("before - velocity %f,%f\n",velocityX,velocityY);
//	int i=0;
	for(Force_it it = forces.begin(); it != forces.end();it++)
	{
		(*it)->affectEntity(m_entity);
//		printf("after %d- velocity %f,%f\n",i++,velocityX,velocityY);
	}

	double norme  = sqrt(forceX*forceX + forceY*forceY);
	if(norme > max_force)
	{
		forceX    *= max_force / norme;
		forceY    *= max_force / norme;
	}


	velocityX += forceX;
	velocityY += forceY;

	norme  = sqrt(velocityX*velocityX + velocityY*velocityY);
	if(norme > max_speed)
	{
		velocityX *= max_speed / norme;
		velocityY *= max_speed / norme;
	}


	//moving body if it's possible
	sf::Vector2f old_pos = m_entity->body()->position();
	m_entity->body()->setPosition(old_pos + sf::Vector2f(velocityX,velocityY));

	if(world.checkBodyCollision(m_entity->body()))
	{
		m_entity->body()->setPosition(old_pos);
		velocityX *= 0;
		velocityY *= 0;
	}

}

void  Physics::thrust(float power)
{
//	velocityX += sin(-m_entity->body()->angle) * power;
//	velocityY += cos(-m_entity->body()->angle) * power;
}

