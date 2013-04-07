/*
 * KeyBoardGamePad.cpp
 *
 * TileGameV2 - Copyright (c) 29 mars 2013 - Jerome Mourey
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
 *  Created on: 29 mars 2013
 */

#include "KeyBoardGamePad.h"
#include <Engine/Entity.h>
#include <Engine/Physics.h>
#include <Engine/platform/PlatformPhysic.h>
#include <SFML/Window/Event.hpp>

KeyBoardGamePad::KeyBoardGamePad(Entity* entity)
: GamePad(entity)
{
}

KeyBoardGamePad::~KeyBoardGamePad()
{
}

void KeyBoardGamePad::handleEvent(const sf::Event& event)
{
	PlatformPhysic& physic = *(PlatformPhysic*)m_entity->physics();
	if(event.type == sf::Event::KeyPressed )
	{
		if(event.key.code == sf::Keyboard::Left)
		{
			if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				physic.move(PlatformPhysic::LEFT);
			}
		}
		else if(event.key.code == sf::Keyboard::C)
		{
			physic.running(true);
		}
		else if(event.key.code == sf::Keyboard::Right)
		{
			if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				physic.move(PlatformPhysic::RIGHT);
			}
		}
		else if(event.key.code == sf::Keyboard::Space)
		{
			physic.jump();
		}
	}
	else if(event.type == sf::Event::KeyReleased)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				physic.move(PlatformPhysic::LEFT);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				physic.move(PlatformPhysic::RIGHT);
			}
		}
		else if(event.key.code == sf::Keyboard::C)
		{
			physic.running(false);
		}
		else
		{
			physic.stop();
		}
	}


}

void KeyBoardGamePad::update()
{

}


