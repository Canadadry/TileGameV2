/*
 * MoveForce.cpp
 *
 * TileGameV2 - Copyright (c) 31 mars 2013 - Jerome Mourey
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
 *  Created on: 31 mars 2013
 */

#include "MoveForce.h"
#include <Engine/Entity.h>
#include <Engine/Physics.h>

MoveForce::MoveForce()
: Force()
, moveLeft(false)
, moveRight(false)
, jump(false)
, m_jump_force(0.0)
, m_move_force(0.0)
{
}

MoveForce::~MoveForce()
{
}

void MoveForce::affectEntity(Entity* entity)
{
	bool* corners = entity->physics()->contact;
	bool isOnFloor = corners[Physics::BottomLeft] || corners[Physics::BottomRight];

	if(moveLeft)
	{
		if(isOnFloor)
		{
				m_move_force = -30;
		}
		else
		{
			m_move_force = -10;
		}

	}
	else if(moveRight)
	{
		if( isOnFloor)
		{
			m_move_force = 30;
		}
		else
		{
			m_move_force = 10;
		}
	}
	else
	{
		m_move_force/=2;
	}
	if(jump)
	{
		if( isOnFloor)
		{
			m_jump_force = -100;
		}
		else if(m_jump_force<=0)
		{
			m_jump_force += 10;
		}
	}
	else
	{
		m_jump_force =0;
	}

	entity->physics()->forceX += m_move_force;
	entity->physics()->forceY += m_jump_force;


}

