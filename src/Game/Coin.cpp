#include "Coin.h"
#include "AnimatedSpriteView.h"

#include <Engine/Body.h>
#include <Engine/View.h>
#include <Graphics/AnimatedTile.h>
#include <Graphics/RessourceManager.h>

#include <SFML/Graphics.hpp>


Coin::Coin(sf::Vector2f pos)
    : Entity()
{

    setBody(new Body());
    body()->setSize(sf::Vector2f(16,16));
    body()->setOrigin(sf::Vector2f(8,8));
    body()->setPosition(pos);

    setView(new AnimatedSpriteView("Animation/coin.txt"));
    name = L"Coin";

}

Coin::~Coin()
{
}


