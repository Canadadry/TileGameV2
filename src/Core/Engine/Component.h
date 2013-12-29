#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

class Component
{
public:
    explicit Component(Entity& entity);
    ~Component();

    virtual void update() ;
protected:
    Entity& entity;
};

#endif /* COMPONENT_H */
