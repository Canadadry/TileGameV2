#ifndef BODY_H_
#define BODY_H_

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <Engine/Component.h>
#include <Signal/Signal.h>

#include <list>

class Body;

struct Contact
{
    Body* thisBody;
    Body* body;
    bool valid;
};

class Body : public Component
{
public:
    Body();
    virtual ~Body();

    void setOrigin(sf::Vector2f origin);
    void setPosition(sf::Vector2f position);
    void setSize(sf::Vector2f size);
    sf::Vector2f position() const;
    sf::Vector2f origin() const;
    sf::Vector2f size() const;

    void move(float x, float y);

    bool intersects(const Body& body) const;

    Signal1< Body* >      beginCollideWidth;
    Signal1< Body* >      endCollideWidth;


    void updateCollision(Body& body);
    virtual void update() ;
    void updateCollideList();

    int collideCategory;
    int collisionMask;
    //	bool isDynamic;

    static Component* build(Entity* entity,JSONValue& param);

private:
    Entity* m_entity;
    sf::FloatRect m_aabb;
    sf::Vector2f m_origin;
    sf::Vector2f m_computedPosition;
    std::list<Contact> m_contactVector;

    void clearContactWith(Body* body);

};

#endif /* BODY_H_ */
