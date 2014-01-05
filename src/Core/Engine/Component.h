#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

class Component
{
public:
    explicit Component(Entity& entity);
    ~Component();

    Entity& entity() const;

    virtual void update() ;
protected:
    Entity& m_entity;
};

#endif /* COMPONENT_H */
