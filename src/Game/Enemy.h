#ifndef ENEMY_H_
#define ENEMY_H_

#include <Engine/Entity.h>
#include <SFML/System/Vector2.hpp>

class TileMapLand;
class PlateformerPhysic;


class Enemy : public Entity
{
public:
	Enemy(/*sf::Vector2f pos ,TileMapLand* land*/);
	virtual ~Enemy();
private:
	PlateformerPhysic* m_plateforme_physics;

};

#endif /* ENEMY_H_ */
