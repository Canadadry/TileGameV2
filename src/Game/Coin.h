#ifndef COIN_H_
#define COIN_H_

#include <Engine/Entity.h>
#include <SFML/System/Vector2.hpp>

class AnimatedTile;
class TileMapLand;


class Coin : public Entity
{
public:
	Coin(sf::Vector2f pos);
	virtual ~Coin();

	virtual void update();
private:
	AnimatedTile* m_sprite;

};

#endif /* PLAYER_H_ */
