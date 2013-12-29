#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/System/Vector2.hpp>

class Body;

class Camera
{
    Camera(sf::Vector2f screenSize);

    void followBody(Body* body);
    void setScreenSize(sf::Vector2f screenSize);
    void setWorldSize(sf::Vector2f worldSize);

    sf::Vector2f origin() const;

    void update();

protected:
    Body*        m_centerBody;
    sf::Vector2f m_screenSize;
    sf::Vector2f m_worldSize;
    sf::Vector2f m_origin_offset;

};

#endif /* CAMERA_H */
