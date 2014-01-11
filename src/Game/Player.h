#ifndef PLAYER_H_
#define PLAYER_H_

#include <Engine/Entity.h>


class AnimatedSpriteView;
class TileMapLand;
class PlateformerPhysic;

class Player : public Entity
{
public:
	Player(TileMapLand* land);
	virtual ~Player();

	virtual void update();
private:
	AnimatedSpriteView* m_sprite_view;
	PlateformerPhysic* m_plateforme_physics;

};

#endif /* PLAYER_H_ */
