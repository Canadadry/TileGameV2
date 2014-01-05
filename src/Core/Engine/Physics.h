#ifndef PHYSICS_H_
#define PHYSICS_H_

#include <SFML/System/Vector2.hpp>
#include <Engine/Component.h>

class Entity;
class World;
class Body;
class TileMapLand;


class Physics : public Component
{
public:
    explicit Physics(Entity& entity);
    virtual ~Physics();
    virtual void  update();

    sf::Vector2f gravity;
    sf::Vector2f speed;
    sf::Vector2f lastPos;
    sf::Vector2f max_speed;

    TileMapLand* land;

    int cornerState() const;

private:
    void checkTileMapCollision();
    void handleCornerCollision(int corner, sf::Vector2f direction);
    void captVector(sf::Vector2f& vector, sf::Vector2f maxAmplitude);

    int          m_cornerState;
};

#endif /* PHYSICS_H_ */
