/*
 * PlatformPhysic.h
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

#ifndef PLATFORMPHYSIC_H_
#define PLATFORMPHYSIC_H_

#include <Engine/Physics.h>

class PlatformPhysic : public Physics
{
public:
	enum Direction{
		UP = -90,
		DOWN = 90,
		LEFT = 180,
		RIGHT = 0
	};
	enum StateFlag{
		MOVING  =0,
		RUNNING ,
		JUMPING ,
		FALLING
	};

	PlatformPhysic(Entity* entity);
	virtual ~PlatformPhysic();

	void move(PlatformPhysic::Direction dir);
	void running(bool enable);
	void jump();
	void stop();


protected:
	virtual void updatedSpeed();
	sf::Vector2f         m_max_speed;
	sf::Vector2f         m_acceleration;
	float                m_jump_power;
	PlatformPhysic::Direction    m_direction;
	bool                  m_state[4];


};

#endif /* PLATFORMPHYSIC_H_ */
