#ifndef GAME_H_
#define GAME_H_


#include <list>
#include <string>
#include <Signal/Signal.h>
#include <Engine/Screen.h>
#include <SFML/Graphics/View.hpp>

class Screen;
class Entity;
class View;
class GamePad;
class Body;
class Physics;
class TileMapLand;

class Game: public Screen
{
public:
    Game(int window_width = 800,int window_height = 600 );
    virtual ~Game();

    virtual void render(sf::RenderTarget* screen_surface);
    virtual void handleEvent(const sf::Event& Event) ;
    virtual void update() ;
    int windowHeight() const;
    int windowWidth() const;

    Signal1<Entity*> entityAdded;
    Signal1<Entity*> entityRemoved;

    sf::View gameView;
    TileMapLand* m_terrain;

protected:
    void addEntity(Entity* entity);
    void destroyedEntity(Entity* entity);
    void onEntityDestroyed(Entity* entity);
    void clear();
    void checkCollision();


private:
    std::list<Entity*>  m_entities_to_destroyed;
    std::list<Entity*>  m_entities;
    std::list<Body*>    m_bodies;
    std::list<View*>    m_views;
    std::list<GamePad*> m_gamepads;
    std::list<Physics*> m_physics;

    int m_window_width;
    int m_window_height;


};

#endif /* GAME_H_ */
