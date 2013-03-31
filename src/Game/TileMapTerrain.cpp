/*
 * TileMapTerrain.cpp
 *
 * TileGameV2 - Copyright (c) 28 mars 2013 - Jerome Mourey
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
 *  Created on: 28 mars 2013
 */

#include "TileMapTerrain.h"
#include <Engine/Body.h>
#include <Engine/Physics.h>
#include <Engine/Entity.h>

TileMapTerrain::TileMapTerrain()
: data(0)
, width_in_tile(0)
, height_in_tile(0)
, tile_size(1)
{}

TileMapTerrain::~TileMapTerrain()
{}

bool TileMapTerrain::isColliding(Body* body)
{
	bool ret = false;

	sf::Vector2f position = body->position();
	sf::Vector2f size     = body->size();

	bool* corners = body->entity()->physics()->contact;

	ret |= corners[Physics::TopLeft    ] = isSolide(position.x       ,position.y       );
	ret |= corners[Physics::TopRight   ] = isSolide(position.x+size.x,position.y       );
	ret |= corners[Physics::BottomLeft ] = isSolide(position.x+size.x,position.y+size.y);
	ret |= corners[Physics::BottomRight] = isSolide(position.x       ,position.y+size.y);

	return ret;
}

bool TileMapTerrain::isSolide(float x, float y)
{
	bool ret = false;
	int id_x = x/(float)tile_size;
	int id_y = y/(float)tile_size;

	if(id_x >= 0 && id_x < width_in_tile)
	{
		if(id_y >= 0 && id_y < height_in_tile)
		{
			ret = data[id_x+width_in_tile*id_y] > 0;
		}
	}

	return ret;
}



