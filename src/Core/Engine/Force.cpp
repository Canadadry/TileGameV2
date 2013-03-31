/*
 * Force.cpp
 *
 * Asteroid - Copyright (c) 3 mars 2013 - Jerome Mourey
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
 *  Created on: 3 mars 2013
 */

#include "Force.h"
#include <Engine/Entity.h>
#include <Engine/Physics.h>
#include <Engine/Body.h>

#include <cmath>

#define PI 3.1415926535

Force::Force()
{
}

Force::~Force()
{
}

Friction::Friction()
: drag(1.0){}

Friction::~Friction(){}

void Friction::affectEntity(Entity* entity)
{
	entity->physics()->velocityX *= entity->physics()->drag;
	entity->physics()->velocityY *= entity->physics()->drag;
}

AttractionPoint::AttractionPoint()
: origin()
, power(1.0)
{}

AttractionPoint::~AttractionPoint(){}

void AttractionPoint::affectEntity(Entity* entity)
{

	float desired_velocityX = (origin.x - entity->body()->position().x);
	float desired_velocityY = (origin.y - entity->body()->position().y);
	float norme  = sqrt(desired_velocityX*desired_velocityX + desired_velocityY*desired_velocityY);
	desired_velocityX /= norme;
	desired_velocityY /= norme;

    float speed_norme  = sqrt(entity->physics()->velocityX*entity->physics()->velocityX
    		                + entity->physics()->velocityY*entity->physics()->velocityY);
    if(speed_norme == 0 )speed_norme = 1.0;
	float steeringX = desired_velocityX - entity->physics()->velocityX/speed_norme;
	float steeringY = desired_velocityY - entity->physics()->velocityY/speed_norme;
	      norme  = sqrt(steeringX*steeringX + steeringY*steeringY);

	steeringX *= power / norme;
	steeringY *= power / norme;

	entity->physics()->forceX += steeringX;
	entity->physics()->forceY += steeringY;

}

AttractionDirection::AttractionDirection()
: angleDirection()
, power(1.0)
{}

AttractionDirection::~AttractionDirection(){}

void AttractionDirection::affectEntity(Entity* entity)
{

	float desired_velocityX = cos(angleDirection/180.0 * PI) ;
	float desired_velocityY = sin(angleDirection/180.0 * PI) ;

    float speed_norme  = sqrt(entity->physics()->velocityX*entity->physics()->velocityX
    		                + entity->physics()->velocityY*entity->physics()->velocityY);

    if(speed_norme == 0 )speed_norme = 1.0;
	float steeringX = desired_velocityX - entity->physics()->velocityX/speed_norme;
	float steeringY = desired_velocityY - entity->physics()->velocityY/speed_norme;
    float norme  = sqrt(steeringX*steeringX + steeringY*steeringY);

	steeringX *= power / norme;
	steeringY *= power / norme;


	entity->physics()->forceX += steeringX;
	entity->physics()->forceY += steeringY;


}
