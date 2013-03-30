/*
 * TileMapTerrain.h
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

#ifndef TILEMAPTERRAIN_H_
#define TILEMAPTERRAIN_H_

#include <Engine/World.h>

class TileMapTerrain : public Terrain
{
public:
	TileMapTerrain();
	virtual ~TileMapTerrain();
	bool isColliding(Body* body);

	int* data;
	int width_in_tile;
	int height_in_tile;
	int tile_size;

private:  bool isSolide(float x,float y);

};

#endif /* TILEMAPTERRAIN_H_ */
