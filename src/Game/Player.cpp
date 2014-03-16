#include "Player.h"
#include "KeyBoardGamePad.h"
#include "PlateformerPhysic.h"
#include "AnimatedSpriteView.h"

#include <Engine/Body.h>
#include <Engine/View.h>
#include <Graphics/AnimatedTile.h>
#include <Graphics/RessourceManager.h>

#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>


Player::Player(TileMapLand* land)
    : Entity()
    , hitEnemy(false)
    , m_sprite_view(new AnimatedSpriteView("Animation/player.txt"))
    , m_plateforme_physics(new PlateformerPhysic(/*land*/))
{
    name =  L"Player";

    setBody(new Body());
    body()->setSize(sf::Vector2f(16,16));
    body()->setOrigin(sf::Vector2f(8,8));
    body()->setPosition(sf::Vector2f(38,38));

    setPhysics(m_plateforme_physics);
    m_plateforme_physics->gravity = sf::Vector2f(0,0.3);
    m_plateforme_physics->max_speed = sf::Vector2f(2.0,8.0);
    m_plateforme_physics->jump_power = 8.0;
    m_plateforme_physics->walk_speed = 2.0;
    m_plateforme_physics->run_speed  = 3.0;
    m_plateforme_physics->walk_deceleration = 0.3;


    setGamepad(new KeyBoardGamePad());

    setView(m_sprite_view);

}

Player::~Player()
{
}

void Player::update()
{
    if(hitEnemy)
    {
	  m_plateforme_physics->state[PlateformerPhysic::Jumping] = true;
	  m_plateforme_physics->speed.y = -5.0;
	  hitEnemy = false;
    }

    int line = 0;
    if(m_plateforme_physics->direction == PlateformerPhysic::Left) line = 1;

    if(m_plateforme_physics->state[PlateformerPhysic::Jumping])
    {
	m_sprite_view->useAnim(3+4*line);
    }
    else if(m_plateforme_physics->state[PlateformerPhysic::Running])
    {
	m_sprite_view->useAnim(2+4*line);
    }
    else if(m_plateforme_physics->state[PlateformerPhysic::Moving])
    {
	m_sprite_view->useAnim(1+4*line);
    }
    else
    {
	m_sprite_view->useAnim(0+4*line);
    }
}
