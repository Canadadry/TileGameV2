#include "Component.h"
#include <iostream>

Component::Component()
    : m_entity(NULL)
{}

Component::~Component(){}

void Component::update() {}

Entity& Component::entity() const
{
    return *m_entity;
}

Component* Component::build(Entity* entity,JSONValue& param)
{
    return NULL;
}
