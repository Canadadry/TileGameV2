/*
 * Force.h
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

#ifndef FORCE_H_
#define FORCE_H_

#include <SFML/System/Vector2.hpp>

class Entity;
class Body;

class Force
{
public:
	Force();
	virtual ~Force();
	virtual void affectEntity(Entity* entity) = 0;
};

//classical Forces :

class Friction : public Force
{
public:
	Friction();
	virtual ~Friction();
	virtual void affectEntity(Entity* entity);

	double drag;
};


class AttractionPoint : public Force
{
public:
	AttractionPoint();
	virtual ~AttractionPoint();
	virtual void affectEntity(Entity* entity);

	sf::Vector2f origin;
	double power;

};

class AttractionDirection : public Force
{
public:
	AttractionDirection();
	virtual ~AttractionDirection();
	virtual void affectEntity(Entity* entity);

	double angleDirection;
	double power;

};



#endif /* FORCE_H_ */
