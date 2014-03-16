#ifndef ANIMATED_SPRITE_VIEW_H_
#define ANIMATED_SPRITE_VIEW_H_

#include <Engine/View.h>

class AnimatedTile;

class AnimatedSpriteView : public View
{
public:
    AnimatedSpriteView();
    AnimatedSpriteView(std::string descriptionFile);
    void buildAnimFromFile(std::string filename);
    virtual ~AnimatedSpriteView();
    void useAnim(unsigned int index);
    unsigned int animCount() const;
    virtual void update();
private:
    AnimatedTile* m_sprite;
    unsigned int m_anim_count;


};

#endif /* ANIMATED_SPRITE_VIEW_H_ */
