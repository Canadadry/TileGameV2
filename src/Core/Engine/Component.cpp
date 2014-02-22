#include "Component.h"
#include <iostream>

Component::Component(Entity& p_entity)
    : m_entity(p_entity)
{}

Component::~Component(){}

void Component::update() {}

Entity& Component::entity() const
{
    return m_entity;
}

Component* Component::build(Entity* entity,JSONValue& param)
{
    return NULL;
}
