#ifndef PLAYER_H_
#define PLAYER_H_

#include <Engine/Entity.h>

class TileMapLand;

class Player : public Entity
{
public:
	Player(TileMapLand* land);
	virtual ~Player();

};

#endif /* PLAYER_H_ */
