#include <Debug/Assert.h>
#include <Engine/Entity.h>
#include <Engine/Body.h>

#include "PlateformerPhysic.h"
#include "TileMapLand.h"

PlateformerPhysic::PlateformerPhysic(Entity& entity,TileMapLand* land)
    : Physics(entity)
    , tilemap(land)
    , m_cornerState(0)
    , m_jump_power(10)
    , m_direction(PlateformerPhysic::Down)
{
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
	gravity.x*=0.3;
    }

    Physics::update();
    ASSERT(tilemap);


    int cornersColliding = m_cornerState = tilemap->checkCornerCollision(entity.body());
    while(cornersColliding != 0)
    {
	if((cornersColliding & TileMapLand::Top) == TileMapLand::Top)
	{
	    entity.body()->move(0.0,1.0);
	    speed.y = 0.0;
	}
	else if((cornersColliding & TileMapLand::Bottom) == TileMapLand::Bottom)
	{
	    entity.body()->move(0.0,-1.0);
	    speed.y = 0.0;
	}
	else if((cornersColliding & TileMapLand::Left) == TileMapLand::Left)
	{
	    entity.body()->move(1.0,0.0);
	    speed.x = 0.0;
	}
	else if((cornersColliding & TileMapLand::Right) == TileMapLand::Right)
	{
	    entity.body()->move(-1.0,0.0);
	    speed.x = 0.0;
	}
	cornersColliding = tilemap->checkCornerCollision(entity.body());
    }
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
    return  ((m_cornerState & TileMapLand::Bottom) == TileMapLand::Bottom);
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
