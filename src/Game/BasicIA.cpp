
#include "BasicIA.h"
#include "PlateformerPhysic.h"
#include <Engine/Entity.h>
#include <Engine/Physics.h>
#include <SFML/Window/Event.hpp>

BasicIA::BasicIA(Entity& entity)
: GamePad(entity)
{
}

BasicIA::~BasicIA()
{
}

//void BasicIA::handleEvent(const sf::Event& event)
//{
//	PlateformerPhysic& physic = *(PlateformerPhysic*)entity().physics();
//	if(event.type == sf::Event::KeyPressed )
//	{
//		if(event.key.code == sf::Keyboard::Left)
//		{
//			if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//			{
//				physic.move(PlateformerPhysic::Left);
//			}
//		}
//		else if(event.key.code == sf::Keyboard::C)
//		{
//			physic.running(true);
//		}
//		else if(event.key.code == sf::Keyboard::Right)
//		{
//			if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//			{
//				physic.move(PlateformerPhysic::Right);
//			}
//		}
//		else if(event.key.code == sf::Keyboard::Space)
//		{
//			physic.jump();
//		}
//	}
//	else if(event.type == sf::Event::KeyReleased)
//	{
//		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//		{
//			if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//			{
//				physic.move(PlateformerPhysic::Left);
//			}
//		}
//		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//		{
//			if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//			{
//				physic.move(PlateformerPhysic::Right);
//			}
//		}
//		else if(event.key.code == sf::Keyboard::C)
//		{
//			physic.running(false);
//		}
//		else
//		{
//			physic.stop();
//		}
//	}


//}

void BasicIA::update()
{
    GamePad::update();
    PlateformerPhysic& physic = *(PlateformerPhysic*)entity().physics();
    if(physic.speed.x == 0.0)
    {
	physic.move(physic.direction==PlateformerPhysic::Left? PlateformerPhysic::Right:PlateformerPhysic::Left);
    }
}


