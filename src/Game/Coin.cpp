#include "Coin.h"

#include <Engine/Body.h>
#include <Engine/View.h>
#include <Graphics/AnimatedTile.h>
#include <Graphics/RessourceManager.h>

#include <SFML/Graphics.hpp>


Coin::Coin(sf::Vector2f pos)
    : Entity()
    , m_sprite(new AnimatedTile)
{

    setBody(new Body(*this));
    body()->setSize(sf::Vector2f(16,16));
    body()->setOrigin(sf::Vector2f(8,8));
    body()->setPosition(pos);

    setView(new View(*this));
    view()->drawable = m_sprite;

    sf::Texture* tileset = RessourceManager::texture().load("/coin.png");

    m_sprite->setTileSet(*tileset,4,1);
    int anim_moving[] = {0,1,2,3};
    std::vector<int> anim ;
    anim.assign(anim_moving,anim_moving+2);
    m_sprite->appendAnimDesc(anim,200);
    m_sprite->useAnim(0);
    m_sprite->setOrigin(8,8);

    name = "Coin";

}

Coin::~Coin()
{
}

void Coin::update()
{
    m_sprite->update();
}
