#include <Engine/Camera.h>
#include <Engine/Body.h>

Camera::Camera(sf::Vector2f screenSize)
    : m_centerBody(NULL)
    , m_screenSize(screenSize)
    , m_worldSize()
    , m_origin_offset()
{}

void Camera::followBody(Body* body)
{
    m_centerBody = body;
}

void Camera::setScreenSize(sf::Vector2f screenSize)
{
    m_screenSize = screenSize;
}

void Camera::setWorldSize(sf::Vector2f worldSize)
{
    m_worldSize = worldSize;
}

sf::Vector2f Camera::origin() const
{
    return m_origin_offset;
}

void Camera::update()
{
    if(m_centerBody == NULL) return;
    if(m_worldSize.x == 0 || m_worldSize.y == 0) return;

    sf::Vector2f mapOrigin = m_centerBody->position();

    if(     mapOrigin.x <  m_screenSize.x/2)                 m_origin_offset.x = m_screenSize.x/2;
    else if(mapOrigin.x > (m_worldSize.x -m_screenSize.x/2)) m_origin_offset.x = (m_worldSize.x -m_screenSize.x/2);
    else m_origin_offset.x = mapOrigin.x;

    if(     mapOrigin.y <  m_screenSize.y/2)                 m_origin_offset.y = m_screenSize.y/2;
    else if(mapOrigin.y > (m_worldSize.y -m_screenSize.y/2)) m_origin_offset.y = (m_worldSize.y -m_screenSize.y/2);
    else m_origin_offset.y = mapOrigin.y;

}
