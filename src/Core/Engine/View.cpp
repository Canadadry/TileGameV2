#include <Engine/View.h>
#include <Engine/Entity.h>
#include <Engine/Body.h>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <Assert.h>

View::View(Entity& entity)
    : Component(entity)
    , drawable(0)
    , m_transformable()
    , m_debugDraw(new sf::RectangleShape())
{
    m_debugDraw->setFillColor(sf::Color::Red);
}

View::~View()
{

}

void View::update()
{
    ASSERT(entity.body());
    if(entity.body())
    {
	m_transformable.setPosition(entity.body()->position());
#ifdef __DEBUG_DRAW__
	m_debugDraw->setPosition(entity.body()->position());
	m_debugDraw->setOrigin(entity.body()->origin());
	m_debugDraw->setSize(entity.body()->size());
#endif
    }
}

void View::render(sf::RenderTarget& screen)
{
    sf::RenderStates states;
    states.transform = m_transformable.getTransform();
#ifdef __DEBUG_DRAW__
    screen.draw(*m_debugDraw,states);
#else
    screen.draw(*drawable,states);
#endif
}


