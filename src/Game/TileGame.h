/*
 * TileGame.h
 *
 * TileGameV2 - Copyright (c) 24 mars 2013 - Jerome Mourey
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
 *  Created on: 24 mars 2013
 */

#ifndef TILEGAME_H_
#define TILEGAME_H_

#include <Engine/Game.h>
#include <Graphics/DrawableGroupe.h>

class Scene2D;
class TileMap;
class TileMapTerrain;
namespace sf{
	class Texture;
	class RenderTexture;
	class Shape;
}

class TileGame : public Game
{
public:
	TileGame(int window_width = 800,int window_height = 600 );
	virtual ~TileGame();

	virtual void render(sf::RenderTarget* screen_surface);
    virtual void update(int elapsedTimeMS) ;

	int m_width_in_tile;
	int m_height_in_tile;

	TileMapTerrain* m_terrain;
	Scene2D* m_scene2D;
	sf::Shape* m_shape;
	Body* trackingPoint;

	DrawableGroupe m_map;

	std::vector<sf::Texture*> m_tilesets;
	std::vector<TileMap*> m_tilemap;
protected:
	virtual void entering() ;

};

#endif /* TILEGAME_H_ */
