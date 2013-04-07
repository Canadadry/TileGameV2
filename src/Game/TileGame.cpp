/*
 * TileGame.cpp
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

#include "Player.h"
#include "TileGame.h"
#include <Loader/Scene2D.h>
#include <Graphics/DrawableGroupe.h>
#include <Graphics/TileMap.h>
#include <Engine/RessourceManager.h>
#include "TileMapTerrain.h"
#include <Engine/Physics.h>
#include <Engine/platform/PlatformPhysic.h>

#include <SFML/Graphics.hpp>

Player* player = 0;

TileGame::TileGame(int window_width ,int window_height )
: Game(window_width ,window_height)
, m_width_in_tile(0)
, m_height_in_tile(0)
, m_terrain(new TileMapTerrain)
, m_scene2D(0)
{
}

TileGame::~TileGame()
{
}

void TileGame::render(sf::RenderTarget* screen_surface)
{
	screen_surface->draw(m_map);
	Game::render(screen_surface);
}

void TileGame::update(int elapsedTimeMS)
{
	Game::update(elapsedTimeMS);
}

void TileGame::handleEvent(const sf::Event& event)
{
	Game::handleEvent(event);
}

void TileGame::entering()
{
	m_scene2D = new Scene2D(RessourceManager::ressourcesDir+"/level_fat.tmx");
	if(!m_scene2D->loadSuccessfull()) return ;

	m_width_in_tile = m_scene2D->width_in_tile;
	m_height_in_tile = m_scene2D->height_in_tile;

	//m_map.setPosition(window_width*m_scene2D->tile_size/2, window_height*m_scene2D->tile_size/2);

	m_tilesets.reserve(m_scene2D->tilesetName.size());
	for(unsigned int i=0;i<m_scene2D->tilesetName.size();i++)
	{
		sf::Texture* text = RessourceManager::texture().load("/"+m_scene2D->tilesetName[i]);
		printf("loading texture %s (%dp,%dp)\n",m_scene2D->tilesetName[i].c_str(),text->getSize().x,text->getSize().y);

		m_tilesets.push_back(text);
	}

	m_tilemap.reserve(m_scene2D->layers.size());
	for(unsigned int i=0;i<m_scene2D->layers.size();i++)
	{

		Scene2D::Layer& layer = *m_scene2D->layers[i];
		sf::Texture& tileset = *m_tilesets[layer.tilesetId];

		printf("new layer found of (%d,%d) tiles (size : %d) using tileset %d\n",
				m_scene2D->width_in_tile,m_scene2D->height_in_tile,m_scene2D->tile_size,layer.tilesetId);

		TileMap* map = new TileMap();
		map->setTileSet(tileset,tileset.getSize().x/m_scene2D->tile_size,tileset.getSize().y/m_scene2D->tile_size);
		map->setData(m_scene2D->width_in_tile,m_scene2D->height_in_tile,(const unsigned int*)&(layer.data[0]));

		m_tilemap.push_back(map);

		m_map.push_back(map);
	}

	m_world.setTerrain(m_terrain);
	m_terrain->data = &(m_scene2D->collision[0]);
	m_terrain->width_in_tile = m_scene2D->width_in_tile;
	m_terrain->height_in_tile = m_scene2D->height_in_tile;
	m_terrain->tile_size = m_scene2D->tile_size;

	player = new Player();
	addEntity(player);

}



