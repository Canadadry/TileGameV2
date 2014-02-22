#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;
class JSONValue;

class Component
{
public:
    explicit Component(Entity& entity);
    ~Component();

    Entity& entity() const;

    virtual void update() ;

    static Component* build(Entity* entity,JSONValue& param);

protected:
    Entity& m_entity;
};

#endif /* COMPONENT_H */
