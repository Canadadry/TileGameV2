#ifndef VIEW_H_
#define VIEW_H_

#include <SFML/Graphics/Transformable.hpp>
#include <Engine/Component.h>

class Entity;
namespace sf{
	class Drawable;
	class RenderTarget;
	class RectangleShape;
}

class View : public Component
{
public:
	View();
	virtual ~View();

	sf::Drawable* drawable;

	virtual void update();
	void render(sf::RenderTarget& screen);

private:
	sf::Transformable   m_transformable;
	sf::RectangleShape* m_debugDraw;
	bool m_enable_debugDraw;

};

#endif /* VIEW_H_ */
