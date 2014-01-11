#ifndef COIN_H_
#define COIN_H_

#include <Engine/Entity.h>
#include <SFML/System/Vector2.hpp>

class Coin : public Entity
{
public:
	Coin(sf::Vector2f pos);
	virtual ~Coin();

};

#endif /* PLAYER_H_ */
