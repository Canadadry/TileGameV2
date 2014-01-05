#include "Component.h"

Component::Component(Entity& p_entity)
    : m_entity(p_entity)
{}

Component::~Component(){}

void Component::update() {}

Entity& Component::entity() const
{
    return m_entity;
}
