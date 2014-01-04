#include <Debug/Assert.h>
#include <Engine/Entity.h>
#include <Engine/Body.h>
#include <Engine/TileMapLand.h>
#include "PlateformerPhysic.h"

PlateformerPhysic::PlateformerPhysic(Entity& entity,TileMapLand* tilemap)
    : Physics(entity)
    , m_jump_power(10)
    , m_direction(PlateformerPhysic::Down)
{
    land = tilemap;
    m_state[PlateformerPhysic::Moving]  = false;
    m_state[PlateformerPhysic::Running] = false;
    m_state[PlateformerPhysic::Jumping] = false;
    m_state[PlateformerPhysic::Falling] = true;
}

PlateformerPhysic::~PlateformerPhysic(){}

void  PlateformerPhysic::update()
{

    if(m_state[PlateformerPhysic::Moving])
    {
	switch(m_direction)
	{
	case PlateformerPhysic::Up    : break;
	case PlateformerPhysic::Down  : break;
	case PlateformerPhysic::Left  : gravity.x = -0.1; break;
	case PlateformerPhysic::Right : gravity.x = 0.1; break;
	}
    }
    else
    {
	gravity.x =0;
	speed.x*=0.3;
    }

    Physics::update();

}

void PlateformerPhysic::move(Direction dir)
{
    m_state[PlateformerPhysic::Moving] = true;
    m_direction = dir;
}

void PlateformerPhysic::stop()
{
    m_state[PlateformerPhysic::Moving] = false;
    m_state[PlateformerPhysic::Running] = false;
}

void PlateformerPhysic::running(bool enable)
{
    m_state[PlateformerPhysic::Running] = enable;
}

bool  PlateformerPhysic::canJump()
{
    return  ((cornerState() & TileMapLand::Bottom) == TileMapLand::Bottom);
}

#define BYTETOBINARYPATTERN "%d%d%d%d%d%d%d%d"
#define BYTETOBINARY(byte)  \
    (byte & 0x80 ? 1 : 0), \
    (byte & 0x40 ? 1 : 0), \
    (byte & 0x20 ? 1 : 0), \
    (byte & 0x10 ? 1 : 0), \
    (byte & 0x08 ? 1 : 0), \
    (byte & 0x04 ? 1 : 0), \
    (byte & 0x02 ? 1 : 0), \
    (byte & 0x01 ? 1 : 0)

void PlateformerPhysic::jump()
{
    printf("state "BYTETOBINARYPATTERN"\n",BYTETOBINARY(m_cornerState));
    if(canJump())
    {
	{
	    m_state[PlateformerPhysic::Jumping] = true;
	    speed.y = -m_jump_power;
	}
    }
}
