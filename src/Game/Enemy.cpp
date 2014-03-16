#include "Enemy.h"
#include "AnimatedSpriteView.h"
#include "PlateformerPhysic.h"
#include "BasicIA.h"

#include <Engine/Body.h>
#include <Engine/View.h>
#include <Graphics/AnimatedTile.h>
#include <Graphics/RessourceManager.h>

#include <SFML/Graphics.hpp>


Enemy::Enemy(sf::Vector2f pos,TileMapLand* land)
    : Entity()
    , m_plateforme_physics(new PlateformerPhysic(land))
{

    setBody(new Body());
    body()->setSize(sf::Vector2f(16,16));
    body()->setOrigin(sf::Vector2f(8,8));
    body()->setPosition(pos);

    setView(new AnimatedSpriteView("Animation/enemy.txt"));

    setPhysics(m_plateforme_physics);
    m_plateforme_physics->gravity = sf::Vector2f(0,0.3);
    m_plateforme_physics->max_speed = sf::Vector2f(1.5,8.0);
    m_plateforme_physics->jump_power = 0.0;
    m_plateforme_physics->walk_speed = 1.5;
    m_plateforme_physics->run_speed  = m_plateforme_physics->walk_speed;
    m_plateforme_physics->walk_deceleration = 0.3;

    setGamepad(new BasicIA());

    name = L"Enemy";

}

Enemy::~Enemy()
{
}


