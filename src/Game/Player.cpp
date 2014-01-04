#include "Player.h"
#include "KeyBoardGamePad.h"
#include "PlateformerPhysic.h"

#include <Engine/Body.h>
#include <Engine/View.h>
#include <Graphics/AnimatedTile.h>
#include <Graphics/RessourceManager.h>

#include <SFML/Graphics.hpp>


Player::Player(TileMapLand* land)
    : Entity()
    , m_sprite(new AnimatedTile)
    , m_plateforme_physics(new PlateformerPhysic(*this,land))
{

    setBody(new Body(*this));
    body()->setSize(sf::Vector2f(16,16));
    body()->setOrigin(sf::Vector2f(8,8));
    body()->setPosition(sf::Vector2f(38,38));

    setPhysics(m_plateforme_physics);
    m_plateforme_physics->gravity = sf::Vector2f(0,0.1);

    setGamepad(new KeyBoardGamePad(*this));

    setView(new View(*this));
    //sf::RectangleShape* shape  = new sf::RectangleShape(sf::Vector2f(16,16));
    //shape->setFillColor(sf::Color::Red);
    view()->drawable = m_sprite;


    sf::Texture* tileset = RessourceManager::texture().load("/mario.png");
    m_sprite->setTileSet(*tileset,5,2);
    int anim_stopped_left[] = {0};
    int anim_moving_left[] = {0,1,2,1};
    int anim_jumping_left[] = {3};
    int anim_stopped_right[] = {5};
    int anim_moving_right[] = {5,6,7,6};
    int anim_jumping_right[] = {8};
    std::vector<int> anim ;
    anim.assign(anim_stopped_left,anim_stopped_left+1);
    m_sprite->appendAnimDesc(anim,100);
    anim.assign(anim_moving_left,anim_moving_left+4);
    m_sprite->appendAnimDesc(anim,100);
    m_sprite->appendAnimDesc(anim,70);
    anim.assign(anim_jumping_left,anim_jumping_left+1);
    m_sprite->appendAnimDesc(anim,100);

    anim.assign(anim_stopped_right,anim_stopped_right+1);
    m_sprite->appendAnimDesc(anim,100);
    anim.assign(anim_moving_right,anim_moving_right+4);
    m_sprite->appendAnimDesc(anim,100);
    m_sprite->appendAnimDesc(anim,70);
    anim.assign(anim_jumping_right,anim_jumping_right+1);
    m_sprite->appendAnimDesc(anim,100);
    m_sprite->useAnim(0);
    m_sprite->setOrigin(8,24);


}

Player::~Player()
{
}

void Player::update()
{
    int line = 0;
    if(m_plateforme_physics->direction == PlateformerPhysic::Left) line = 1;

    if(m_plateforme_physics->state[PlateformerPhysic::Jumping])
    {
	m_sprite->useAnim(3+4*line);
    }
    else if(m_plateforme_physics->state[PlateformerPhysic::Running])
    {
	m_sprite->useAnim(2+4*line);
    }
    else if(m_plateforme_physics->state[PlateformerPhysic::Moving])
    {
	m_sprite->useAnim(1+4*line);
    }
    else
    {
	m_sprite->useAnim(0+4*line);
    }
    m_sprite->update();
}
