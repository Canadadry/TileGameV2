#include <Engine/Entity.h>
#include <Engine/Physics.h>
#include <Engine/Body.h>
#include <Engine/TileMapLand.h>
#include <Debug/Assert.h>

#include <cmath>

Physics::Physics(Entity& entity)
    : Component (entity)
    , gravity(0.0,0.0)
    , speed (0.0,0.0)
    , max_speed(10.0,10.0)
    , land(NULL)
    , m_cornerState(0)
{
}

Physics::~Physics()
{
}

void  Physics::update()
{
    ASSERT(entity.body());

    lastPos = entity().body()->position();
    speed += gravity /* * dt*/;
    captVector(speed,max_speed);
    sf::Vector2f pos = entity().body()->position();
    pos += speed /* *dt */;
    pos.x = roundf(pos.x);
    pos.y = roundf(pos.y);

    entity().body()->setPosition(pos);

    if(land != NULL)
    {
	checkTileMapCollision();
    }
}

int Physics::cornerState() const
{
    return m_cornerState;
}

void Physics::checkTileMapCollision()
{
    m_cornerState = land->checkCornerCollision(entity().body());
    if(m_cornerState != 0)
    {
	handleCornerCollision(TileMapLand::Bottom      ,sf::Vector2f( 0.0,-1.0));
	handleCornerCollision(TileMapLand::Top         ,sf::Vector2f( 0.0, 1.0));
	handleCornerCollision(TileMapLand::Left        ,sf::Vector2f( 1.0, 0.0));
	handleCornerCollision(TileMapLand::Right       ,sf::Vector2f(-1.0, 0.0));
	handleCornerCollision(TileMapLand::TopLeft     ,sf::Vector2f( 1.0, 1.0));
	handleCornerCollision(TileMapLand::TopRight    ,sf::Vector2f(-1.0, 1.0));
	handleCornerCollision(TileMapLand::BottomLeft  ,sf::Vector2f( 1.0,-1.0));
	handleCornerCollision(TileMapLand::BottomRight ,sf::Vector2f(-1.0,-1.0));
    }
}

void Physics::handleCornerCollision(int corner, sf::Vector2f direction)
{
    bool hasMoved = false;
    while((land->checkCornerCollision(entity().body()) & corner) == corner)
    {
	entity().body()->move(direction.x,direction.y);
	hasMoved = true;
    }
    if(hasMoved)
    {
	entity().body()->move(-direction.x,-direction.y);
	if(direction.x == 0  ||  direction.y == 0)
	{
	    if(direction.x != 0 && (signbit(direction.x) != signbit(speed.x)))
	    {
		speed.x = 0;
	    }
	    if(direction.y != 0 && (signbit(direction.y) != signbit(speed.y)))
	    {
		speed.y = 0;
	    }
	}
    }
}


void Physics::captVector(sf::Vector2f& vector, sf::Vector2f maxAmplitude)
{
//    std::cout << "speed before " << vector.x << "," << vector.y ;

    if(fabs(vector.x) > maxAmplitude.x) vector.x = copysign(maxAmplitude.x,vector.x);
    if(fabs(vector.y) > maxAmplitude.y) vector.y = copysign(maxAmplitude.y,vector.y);

//    std::cout << " speed after  " << vector.x << "," << vector.y ;
//    std::cout << std::endl;

}
