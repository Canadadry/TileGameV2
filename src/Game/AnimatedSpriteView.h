#ifndef ANIMATED_SPRITE_VIEW_H_
#define ANIMATED_SPRITE_VIEW_H_

#include <Engine/View.h>
#include <string>


class AnimatedTile;

class AnimatedSpriteView : public View
{
public:
	AnimatedSpriteView(Entity& entity,std::string descriptionFile);
	virtual ~AnimatedSpriteView();
	void useAnim(unsigned int index);
	unsigned int animCount() const;
	virtual void update();
private:
	AnimatedTile* m_sprite;
	unsigned int m_anim_count;
	void buildAnimFromFile(std::string filename);

};

#endif /* ANIMATED_SPRITE_VIEW_H_ */
