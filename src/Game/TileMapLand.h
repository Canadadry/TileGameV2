#ifndef TILEMAPLAND_H_
#define TILEMAPLAND_H_


class Body;

class TileMapLand
{
public:
    enum{
	TopLeft	    = 1<<0,
	Top         = 1<<1,
	TopRight    = 1<<2,
	Left	    = 1<<3,
	Right       = 1<<4,
	BottomLeft  = 1<<5,
	Bottom      = 1<<6,
	BottomRight = 1<<7
    } Corner;

    TileMapLand();
    virtual ~TileMapLand();
    int checkCornerCollision(Body* body);

    int* data;
    int width_in_tile;
    int height_in_tile;
    int tile_size;

private:
    bool isSolide(float x,float y);

};

#endif /* TILEMAPLAND_H_ */
