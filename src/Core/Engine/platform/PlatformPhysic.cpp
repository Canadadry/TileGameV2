/*
 * PlatformPhysic.cpp
 *
 * TileGameV2 - Copyright (c) 1 avr. 2013 - Jerome Mourey
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
 *  Created on: 1 avr. 2013
 */

#include "PlatformPhysic.h"
#include <cmath>
#include <cstdio>

const float   tile_size = 16.0;
const float max_height_jump = tile_size*6.5;
float elapsedTimeMS = 16; //ms

// spe



struct EntityBehavior{
//	EntityBehavior();
	EntityBehavior( float   p_gravity           = 0.1 *tile_size/elapsedTimeMS/elapsedTimeMS    ,  //force
					float   p_max_falling_speed = 10.0*tile_size/elapsedTimeMS    ,                //vitesse
					float   p_mvt_speed         = 3.0 *tile_size/elapsedTimeMS    ,                //vitesse
					float   p_running_speed     = 7.0 *tile_size/elapsedTimeMS    ,                //vitesse
					float   p_mvt_acc           = 9.0 *tile_size/elapsedTimeMS/elapsedTimeMS    ,                //force
					float   p_size              = 0.6                       )                       //useless
	:gravity          (p_gravity          )
	,max_falling_speed(p_max_falling_speed)
	,mvt_speed        (p_mvt_speed        )
	,running_speed    (p_running_speed    )
	,mvt_acc          (p_mvt_acc          )
	,size             (p_size             )
	,jump_impulse     (sqrt(2*p_gravity*max_height_jump)) //20.0*32.0 / 1000.0  )  //hauteur max = 0.5*jump_impulse^2/gravity en pix
	{}

	const float   gravity          ;
	const float   max_falling_speed;
	const float   mvt_speed        ;
	const float   running_speed    ;
	const float   mvt_acc          ;
	const float   size             ;
	const float   jump_impulse     ;

//	static const EntityBehavior PLAYER;
//	static const EntityBehavior MOB;
};

EntityBehavior m_behavior;

PlatformPhysic::PlatformPhysic(Entity* entity)
: Physics(entity)
, m_max_speed(m_behavior.running_speed,m_behavior.max_falling_speed)
, m_acceleration(m_behavior.mvt_acc,m_behavior.gravity)
, m_direction(PlatformPhysic::DOWN)
{
	m_state[PlatformPhysic::MOVING]  = false;
	m_state[PlatformPhysic::RUNNING] = false;
	m_state[PlatformPhysic::JUMPING] = false;
	m_state[PlatformPhysic::FALLING] = true;
}

PlatformPhysic::~PlatformPhysic()
{
}


void PlatformPhysic::move(Direction dir)
{
	printf("MOVING\n");

	m_state[PlatformPhysic::MOVING] = true;
	m_direction = dir;
}

void PlatformPhysic::stop()
{
	printf("STOP\n");
	m_state[PlatformPhysic::MOVING] = false;
	m_state[PlatformPhysic::RUNNING] = false;
}


void PlatformPhysic::running(bool enable)
{
	m_state[PlatformPhysic::RUNNING] = enable;
	m_max_speed.x = enable ? m_behavior.running_speed : m_behavior.mvt_speed;
}

void PlatformPhysic::jump()
{
	printf("JUMP\n");
	if(m_state[PlatformPhysic::JUMPING] == false)
	{
		if(m_speed.y < 1.0)
		{
			m_state[PlatformPhysic::JUMPING] = true;
			m_speed.y = -m_behavior.jump_impulse;

		}
	}
}

void PlatformPhysic::updatedSpeed()
{

	if(fabs(m_speed.y) < 0.1)
	{
		m_state[PlatformPhysic::JUMPING] = false;
	}
	// x speed
	if(m_state[PlatformPhysic::MOVING])
	{
		printf("isMoving\n");
		switch(m_direction)
		{
			case PlatformPhysic::UP    : break;
			case PlatformPhysic::DOWN  : break;
			case PlatformPhysic::LEFT  : m_speed.x -= m_acceleration.x*elapsedTimeMS; break;
			case PlatformPhysic::RIGHT : m_speed.x += m_acceleration.x*elapsedTimeMS; break;
		}

		if(fabs(m_speed.x) > fabs(m_max_speed.x) )
		{
			m_speed.x = (m_speed.x > 0)? m_max_speed.x:-m_max_speed.x;
		}
	}
	else
	{
		m_speed.x*=0.5;
	}


	//y speed
	m_speed.y += m_behavior.gravity*elapsedTimeMS;
	if(fabs(m_speed.y) > fabs(m_max_speed.y) )
	{
		m_speed.y = (m_speed.y > 0)? m_max_speed.y:-m_max_speed.y;
	}
}


