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

// unit : pixel and frame

PlatformPhysic::PlatformPhysic(Entity* entity)
: Physics(entity)
, m_max_speed(4,10)
, m_acceleration(0.6,0.6)
, m_jump_power(120)
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
	//m_max_speed.x = enable ? m_behavior.running_speed : m_behavior.mvt_speed;
}

void PlatformPhysic::jump()
{
	printf("JUMP\n");
	if(m_state[PlatformPhysic::JUMPING] == false)
	{
		if(m_speed.y < 1.0)
		{
			m_state[PlatformPhysic::JUMPING] = true;
			m_speed.y = -m_jump_power;

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
			case PlatformPhysic::LEFT  : m_speed.x -= m_acceleration.x; break;
			case PlatformPhysic::RIGHT : m_speed.x += m_acceleration.x; break;
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
	m_speed.y += m_acceleration.y;
	if(fabs(m_speed.y) > fabs(m_max_speed.y) )
	{
		m_speed.y = (m_speed.y > 0)? m_max_speed.y:-m_max_speed.y;
	}
}


