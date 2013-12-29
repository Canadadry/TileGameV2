#ifndef ENTITY_H_
#define ENTITY_H_

#include <Signal/Signal.h>
#include <string>

class Body;
class Physics;
class View;
class GamePad;
class Game;

class Entity
{
public:
    Entity();
    virtual ~Entity();

    //ACTION
    virtual void update();

    // COMPONENTS
    Body*                body()          const;
    Physics*             physics()       const;
    View*                view()          const;
    GamePad*             gamepad()       const;
    void setBody         (Body* body);
    void setPhysics      (Physics* physics);
    void setView         (View* view);
    void setGamepad      (GamePad* gamepad);

    // SIGNALS
    Signal1< Entity* >      entityCreated;
    Signal1< Entity* >      destroyed;

    bool                    isAlive();

    std::string        name;
    Game*              game;

protected:
    void destroyThis();

private:
    Body*    m_body;
    Physics* m_physics;
    View*    m_view;
    GamePad* m_gamepad;
    bool     m_isAlive;

};

#endif /* ENTITY_H_ */
