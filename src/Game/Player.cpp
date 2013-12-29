#include "Player.h"
#include "KeyBoardGamePad.h"
#include "PlateformerPhysic.h"

#include <Engine/Body.h>
#include <Engine/View.h>

#include <Graphics/RessourceManager.h>

#include <SFML/Graphics/RectangleShape.hpp>



Player::Player(TileMapLand* land)
: Entity()
{

	setBody(new Body(*this));
	body()->setSize(sf::Vector2f(16,16));
	body()->setPosition(sf::Vector2f(38,38));

	setPhysics(new PlateformerPhysic(*this,land));
	this->physics()->gravity = sf::Vector2f(0,0.1);
	setGamepad(new KeyBoardGamePad(*this));

	setView(new View(*this));
	sf::RectangleShape* shape  = new sf::RectangleShape(sf::Vector2f(16,16));
	shape->setFillColor(sf::Color::Red);
	view()->drawable = shape;


}

Player::~Player()
{
}

