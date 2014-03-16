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

    PlateformerPhysic(TileMapLand* land);
    virtual ~PlateformerPhysic();

    bool canJump();

    void move(Direction dir);
    void jump();
    void running(bool enable);
    void stop();

    virtual void  update();
    Direction    direction;
    bool         state[4];

    float jump_power;
    float walk_speed;
    float run_speed;
    float walk_deceleration;

};

#endif /* _PLATEFORMERPHYSIC_H_ */
