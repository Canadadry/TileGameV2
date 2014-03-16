
#include "BasicIA.h"
#include "PlateformerPhysic.h"
#include <Engine/Entity.h>
#include <Engine/Physics.h>
#include <SFML/Window/Event.hpp>

BasicIA::BasicIA()
: GamePad()
{
}

BasicIA::~BasicIA()
{
}

void BasicIA::update()
{
    GamePad::update();
    PlateformerPhysic& physic = *(PlateformerPhysic*)entity().physics();
    if(physic.speed.x == 0.0)
    {
	physic.move(physic.direction==PlateformerPhysic::Left? PlateformerPhysic::Right:PlateformerPhysic::Left);
    }
}


