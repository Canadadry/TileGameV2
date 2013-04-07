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
#include <Engine/Entity.h>
#include <Engine/Body.h>

// unit : pixel and frame

PlatformPhysic::PlatformPhysic(Entity* entity)
: Physics(entity)
, m_max_speed(2,8)
, m_acceleration(0.6,0.4)
, m_jump_power(140)
, m_direction(PlatformPhysic::DOWN)
, m_frameOnWall(0)
, m_wallJumpCount(0)
, m_jumpFrame(0)
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
	m_state[PlatformPhysic::MOVING] = true;
	m_direction = dir;
}

void PlatformPhysic::stop()
{
	m_state[PlatformPhysic::MOVING] = false;
	m_state[PlatformPhysic::RUNNING] = false;
}


void PlatformPhysic::running(bool enable)
{
	m_state[PlatformPhysic::RUNNING] = enable;
}

void PlatformPhysic::jump()
{
	if( m_entity->body()->isOnFloor())
	{
		{
			m_state[PlatformPhysic::JUMPING] = true;
			m_speed.y = -m_jump_power;
		}
	}
	else
	{
		if(m_frameOnWall>0 && m_frameOnWall < 10)
		{
			if(m_wallJumpCount < 3)
			{
				m_wallJumpCount++;
				m_speed.y = -m_jump_power;
				switch(m_direction)
				{
					case PlatformPhysic::UP    : break;
					case PlatformPhysic::DOWN  : break;
					case PlatformPhysic::LEFT  : m_speed.x =  m_max_speed.x; break;
					case PlatformPhysic::RIGHT : m_speed.x = -m_max_speed.x; break;
				}
			}
		}
	}
}

void PlatformPhysic::updatedSpeed()
{

	if(m_entity->body()->touchingWall() && ! m_entity->body()->isOnFloor())
	{
		m_frameOnWall++;
	}
	else
	{
		m_frameOnWall = 0;
	}

	// x speed
	if(m_state[PlatformPhysic::MOVING])
	{
		float jump_factor = 1.0;
		if(! m_entity->body()->isOnFloor())
		{
			jump_factor = 0.5;
		}
		switch(m_direction)
		{
			case PlatformPhysic::UP    : break;
			case PlatformPhysic::DOWN  : break;
			case PlatformPhysic::LEFT  : m_speed.x -= m_acceleration.x*jump_factor; break;
			case PlatformPhysic::RIGHT : m_speed.x += m_acceleration.x*jump_factor; break;
		}

		if(fabs(m_speed.x) > fabs(m_max_speed.x) )
		{
			m_speed.x = (m_speed.x > 0)? m_max_speed.x:-m_max_speed.x;
		}
	}
	else
	{
		m_speed.x*=0.3;
	}

	//y speed
	if(m_entity->body()->isAABBCornerFree[Body::Bottom] )
	{
		m_state[PlatformPhysic::JUMPING] = false;
		m_state[PlatformPhysic::FALLING] = false;
		m_wallJumpCount = 0;
	}
	else if(m_speed.y > 0)
	{
		m_state[PlatformPhysic::FALLING] = true;
	}

	m_speed.y += m_acceleration.y;
	if(fabs(m_speed.y) > fabs(m_max_speed.y) )
	{
		m_speed.y = (m_speed.y > 0)? m_max_speed.y:-m_max_speed.y;
	}

}


