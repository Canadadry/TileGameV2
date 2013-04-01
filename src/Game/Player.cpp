/*
 * Player.cpp
 *
 * TileGameV2 - Copyright (c) 30 mars 2013 - Jerome Mourey
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
 *  Created on: 30 mars 2013
 */

#include "Player.h"
#include <Engine/Body.h>
#include <Engine/Physics.h>
#include <Engine/View.h>
#include <Engine/RessourceManager.h>

#include <SFML/Graphics.hpp>



Player::Player()
: Entity()
//, m_sprite(new sf::Sprite )
{

	setBody(new Body(this));
	body()->setSize(sf::Vector2f(16,16));
	//body()->setOrigin(sf::Vector2f(8,8));
	body()->setPosition(sf::Vector2f(38,38));

	//setPhysics(new Physics(this));

	setView(new View(this));
	sf::RectangleShape* shape  = new sf::RectangleShape(sf::Vector2f(16,16));
	//shape->setOrigin(sf::Vector2f(8,8));
	shape->setFillColor(sf::Color::Red);
	view()->drawable = shape;


}

Player::~Player()
{
}

