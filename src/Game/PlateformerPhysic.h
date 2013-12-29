#ifndef _PLATEFORMERPHYSIC_H_
#define _PLATEFORMERPHYSIC_H_

#include <Engine/Physics.h>

class TileMapLand;
class Entity;

class PlateformerPhysic : public Physics
{
public:
    enum Direction {Left,Right,Top,Bottom} ;
    PlateformerPhysic(Entity& entity, TileMapLand* land);
    virtual ~PlateformerPhysic();

    void move(Direction dir);
    void jump();
    void running(bool enable);
    void stop();

    virtual void  update();

    TileMapLand* tilemap;

};

#endif /* _PLATEFORMERPHYSIC_H_ */
