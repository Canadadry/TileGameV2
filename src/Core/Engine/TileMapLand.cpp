#include "TileMapLand.h"
#include <Engine/Body.h>

TileMapLand::TileMapLand()
    : data(0)
    , width_in_tile(0)
    , height_in_tile(0)
    , tile_size(1)
{}

TileMapLand::~TileMapLand()
{}

int TileMapLand::checkCornerCollision(Body* body)
{
    int collidingCorners = 0;
    sf::Vector2f position = body->position() - body->origin();
    sf::Vector2f size     = body->size();
    sf::Vector2f size2    = sf::Vector2f(size.x/2.0,size.y/2.0);

    collidingCorners =   collidingCorners | (isSolide(position.x           , position.y           ) ? TopLeft     : 0);
    collidingCorners =   collidingCorners | (isSolide(position.x + size2.x , position.y           ) ? Top         : 0);
    collidingCorners =   collidingCorners | (isSolide(position.x + size.x  , position.y           ) ? TopRight    : 0);
    collidingCorners =   collidingCorners | (isSolide(position.x           , position.y + size2.y ) ? Left        : 0);
    collidingCorners =   collidingCorners | (isSolide(position.x + size.x  , position.y + size2.y ) ? Right       : 0);
    collidingCorners =   collidingCorners | (isSolide(position.x           , position.y + size.y  ) ? BottomLeft  : 0);
    collidingCorners =   collidingCorners | (isSolide(position.x + size2.x , position.y + size.y  ) ? Bottom      : 0);
    collidingCorners =   collidingCorners | (isSolide(position.x + size.x  , position.y + size.y  ) ? BottomRight : 0);

    return collidingCorners;
}

bool TileMapLand::isSolide(float x, float y)
{
    bool ret = false;
    int id_x = x/(float)tile_size;
    int id_y = y/(float)tile_size;

    if(id_x >= 0 && id_x < width_in_tile)
    {
	if(id_y >= 0 && id_y < height_in_tile)
	{
	    ret = data[id_x+width_in_tile*id_y] > 0;
	}
    }

    return ret;
}



