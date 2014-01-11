#include <Engine/View.h>
#include <Engine/Entity.h>
#include <Engine/Body.h>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <Debug/Assert.h>

View::View(Entity& entity)
    : Component(entity)
    , drawable(0)
    , m_transformable()
    , m_debugDraw(new sf::RectangleShape())
    , m_enable_debugDraw(false)
{
    m_debugDraw->setOutlineColor(sf::Color::Red);
    m_debugDraw->setFillColor(sf::Color::Transparent);
    m_debugDraw->setOutlineThickness(2.0);
}

View::~View()
{

}


void View::update()
{
    ASSERT(entity().body());
    if(entity().body())
    {
	m_transformable.setPosition(entity().body()->position());
	if(m_enable_debugDraw)
	{
	    m_debugDraw->setOrigin(entity().body()->origin());
	    m_debugDraw->setSize(entity().body()->size());
	}
    }
}

void View::render(sf::RenderTarget& screen)
{
    ASSERT(drawable);
    sf::RenderStates states;
    states.transform = m_transformable.getTransform();
    if(m_enable_debugDraw) screen.draw(*m_debugDraw,states);
    screen.draw(*drawable,states);
}


