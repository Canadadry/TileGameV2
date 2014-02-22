#include <Engine/GamePad.h>

GamePad::GamePad(Entity& entity)
: Component(entity)
{
}

GamePad::~GamePad()
{
}


void GamePad::handleEvent(const sf::Event& Event)
{

}

Component* GamePad::build(Entity* entity,JSONValue& param)
{
    return new GamePad(*entity);
}
