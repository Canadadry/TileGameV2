#include "Player.h"
#include "TileGame.h"
#include <Loader/Scene2D.h>
#include <Graphics/DrawableGroupe.h>
#include <Graphics/TileMap.h>
#include <Graphics/RessourceManager.h>
#include <Engine/TileMapLand.h>
#include <Engine/Physics.h>

#include <SFML/Graphics.hpp>

Player* player = 0;

TileGame::TileGame(int window_width ,int window_height )
: Game(window_width ,window_height)
, m_width_in_tile(0)
, m_height_in_tile(0)
, m_terrain(new TileMapLand)
, m_scene2D(0)
, m_map()
, m_camera(sf::Vector2f(window_width,window_height))
, m_tilesets()
, m_tilemap()
, m_tilemap_land(NULL)
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

void TileGame::update()
{
	Game::update();
	m_camera.update();
	gameView.setCenter(m_camera.origin());
	//m_map.setOrigin(m_camera.origin());
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

	//m_map.setPosition(windowWidth()/2, windowHeight()/2);
	m_camera.setWorldSize(sf::Vector2f(m_width_in_tile*m_scene2D->tile_size,m_height_in_tile*m_scene2D->tile_size));

	m_tilesets.reserve(m_scene2D->tilesetName.size());
	for(unsigned int i=0;i<m_scene2D->tilesetName.size();i++)
	{
		sf::Texture* text = RessourceManager::texture().load("/"+m_scene2D->tilesetName[i]);
		m_tilesets.push_back(text);
	}

	m_tilemap.reserve(m_scene2D->layers.size());
	for(unsigned int i=0;i<m_scene2D->layers.size();i++)
	{

		Scene2D::Layer& layer = *m_scene2D->layers[i];
		sf::Texture& tileset = *m_tilesets[layer.tilesetId];

		TileMap* map = new TileMap();
		map->setTileSet(tileset,tileset.getSize().x/m_scene2D->tile_size,tileset.getSize().y/m_scene2D->tile_size);
		map->setData(m_scene2D->width_in_tile,m_scene2D->height_in_tile,(const unsigned int*)&(layer.data[0]));

		m_tilemap.push_back(map);

		m_map.push_back(map);
	}

	m_terrain->data = &(m_scene2D->collision[0]);
	m_terrain->width_in_tile = m_scene2D->width_in_tile;
	m_terrain->height_in_tile = m_scene2D->height_in_tile;
	m_terrain->tile_size = m_scene2D->tile_size;

	player = new Player(m_terrain);
	m_camera.followBody(player->body());
	addEntity(player);

}



