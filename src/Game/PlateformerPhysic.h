#ifndef _PLATEFORMERPHYSIC_H_
#define _PLATEFORMERPHYSIC_H_

#include <Engine/Physics.h>

class TileMapLand;
class Entity;

class PlateformerPhysic : public Physics
{
public:
    enum Direction {Left,Right,Up,Down} ;
    enum StateFlag{
	Moving  =0,
	Running ,
	Jumping ,
	Falling
    };

    PlateformerPhysic(Entity& entity, TileMapLand* land);
    virtual ~PlateformerPhysic();

    bool canJump();

    void move(Direction dir);
    void jump();
    void running(bool enable);
    void stop();

    virtual void  update();

protected:
    TileMapLand* tilemap;
    int          m_cornerState;
    float        m_jump_power;
    Direction    m_direction;
    bool         m_state[4];

};

#endif /* _PLATEFORMERPHYSIC_H_ */
