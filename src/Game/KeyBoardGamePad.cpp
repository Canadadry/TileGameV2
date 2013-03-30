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

KeyBoardGamePad::KeyBoardGamePad(Entity* entity)
: GamePad(entity)
{
}

KeyBoardGamePad::~KeyBoardGamePad()
{
}

void KeyBoardGamePad::handleEvent(const sf::Event& Event)
{
}

void KeyBoardGamePad::update()
{
//	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//	{
//		m_entity->body()->angle -= 0.04;
//	}
//	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//	{
//		m_entity->body()->angle += 0.04;
//	}
//	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//	{
//		m_entity->physics()->thrust(-0.4);
//	}
//	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//	{
//		m_entity->physics()->thrust(0.4);
//	}
//
//	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//	{
//		m_entity->weapon()->fire();
//	}

}

