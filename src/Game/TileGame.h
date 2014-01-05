#ifndef TILEGAME_H_
#define TILEGAME_H_

#include <Engine/Game.h>
#include <Engine/Camera.h>
#include <Graphics/DrawableGroupe.h>

class Scene2D;
class TileMap;
class TileMapLand;
class Camera;

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
    virtual void update() ;
    virtual void handleEvent(const sf::Event& Event);

protected:
    virtual void entering() ;

    int m_width_in_tile;
    int m_height_in_tile;

    TileMapLand* m_terrain;
    Scene2D* m_scene2D;

    DrawableGroupe m_map;
    Camera     m_camera;

    std::vector<sf::Texture*> m_tilesets;
    std::vector<TileMap*> m_tilemap;
    TileMapLand* m_tilemap_land;

    Entity* m_player;

};

#endif /* TILEGAME_H_ */
