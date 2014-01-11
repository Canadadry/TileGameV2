#include "Player.h"
#include "Coin.h"
#include "Enemy.h"
#include "TileGame.h"
#include <Loader/Scene2D.h>
#include <Graphics/DrawableGroupe.h>
#include <Graphics/TileMap.h>
#include <Graphics/RessourceManager.h>
#include <Engine/TileMapLand.h>
#include <Engine/Physics.h>
#include <Engine/Body.h>

#include <SFML/Graphics.hpp>

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
, m_player(NULL)
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
	if(m_player->body()->position().y > (m_height_in_tile+1)*m_scene2D->tile_size )
	{
	    setNextScreen(new TileGame(windowWidth(),windowHeight()));
	}
	m_camera.update();
	gameView.setCenter(m_camera.origin());
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

	m_player = new Player(m_terrain);
	m_player->body()->beginCollideWidth.Connect(this,&TileGame::handlePlayerCollision);
	m_camera.followBody(m_player->body());
	addEntity(m_player);

	for(unsigned int i=0;i<m_scene2D->entities.size();i++)
	{
		Scene2D::Entity& entity = m_scene2D->entities[i];
		Entity* mob = 0;
		//		printf("entity id is %d\n",entity.entityId);
		switch(entity.entityId)
		{
			case 2 :  mob = new Enemy(sf::Vector2f(entity.x+0.5,entity.y+0.5)*(float)m_scene2D->tile_size,m_terrain);break;
			case 3 :  mob = new Coin(sf::Vector2f(entity.x+0.5,entity.y+0.5)*(float)m_scene2D->tile_size);break;
			case 0 :  break;
			case 1 :  break;
			default : break;
		}
		if(mob != NULL)
		{
			addEntity(mob);
		}
	}


}


void TileGame::handlePlayerCollision(Body* obstacle)
{
    if(obstacle->entity().name == "Coin") obstacle->entity().destroyThis();
}

