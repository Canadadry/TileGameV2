#include "Component.h"

Component::Component(Entity& p_entity)
    : entity(p_entity)
{}

Component::~Component(){}

void Component::update() {}
