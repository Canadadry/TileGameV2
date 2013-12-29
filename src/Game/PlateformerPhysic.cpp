#include <Debug/Assert.h>
#include <Engine/Entity.h>
#include <Engine/Body.h>

#include "PlateformerPhysic.h"
#include "TileMapLand.h"

PlateformerPhysic::PlateformerPhysic(Entity& entity,TileMapLand* land)
    : Physics(entity)
    , tilemap(land)
{}

PlateformerPhysic::~PlateformerPhysic(){}

void  PlateformerPhysic::update()
{
    Physics::update();
    ASSERT(tilemap);

    int cornersColliding = tilemap->checkCornerCollision(entity.body());
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

}

void PlateformerPhysic::jump()
{

}

void PlateformerPhysic::running(bool enable)
{

}

void PlateformerPhysic::stop()
{

}
