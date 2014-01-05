#include <Debug/Assert.h>
#include <Engine/Entity.h>
#include <Engine/Body.h>
#include <Engine/TileMapLand.h>
#include "PlateformerPhysic.h"

PlateformerPhysic::PlateformerPhysic(Entity& entity,TileMapLand* tilemap)
    : Physics(entity)
    , direction(PlateformerPhysic::Down)
    , jump_power(1)
    , walk_speed(0.1)
    , run_speed(1.0)
    , walk_deceleration(0.3)
{
    land = tilemap;
    state[PlateformerPhysic::Moving]  = false;
    state[PlateformerPhysic::Running] = false;
    state[PlateformerPhysic::Jumping] = false;
    state[PlateformerPhysic::Falling] = true;
}

PlateformerPhysic::~PlateformerPhysic(){}

void  PlateformerPhysic::update()
{

    if(state[PlateformerPhysic::Moving])
    {
	switch(direction)
	{
	case PlateformerPhysic::Up    : break;
	case PlateformerPhysic::Down  : break;
	case PlateformerPhysic::Left  : gravity.x = -walk_speed; break;
	case PlateformerPhysic::Right : gravity.x =  walk_speed; break;
	}
    }
    else
    {
	gravity.x =0;
	speed.x*=walk_deceleration;
    }

    Physics::update();

    state[PlateformerPhysic::Jumping] = (speed.y != 0);
}

void PlateformerPhysic::move(Direction dir)
{
    state[PlateformerPhysic::Moving] = true;
    direction = dir;
}

void PlateformerPhysic::stop()
{
    state[PlateformerPhysic::Moving] = false;
    state[PlateformerPhysic::Running] = false;
}

void PlateformerPhysic::running(bool enable)
{
    state[PlateformerPhysic::Running] = enable;
    max_speed.x = enable ? run_speed : walk_speed;
}

bool  PlateformerPhysic::canJump()
{
    return  ((cornerState() & TileMapLand::Bottom) == TileMapLand::Bottom);
}

void PlateformerPhysic::jump()
{
    if(canJump())
    {
	{
	    state[PlateformerPhysic::Jumping] = true;
	    speed.y = -jump_power;
	}
    }
}
