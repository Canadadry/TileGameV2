#ifndef   _FACTORY_GLUE__
#define  _FACTORY_GLUE__

#include <Factory/Factory.h>

#include "AnimatedSpriteView.h"
#include "BasicIA.h"
#include "KeyBoardGamePad.h"
#include "PlateformerPhysic.h"

class BasicIABuilder : public RegisterToFactory<BasicIABuilder,BasicIA>{};

class KeyBoardGamePadBuilder : public RegisterToFactory<KeyBoardGamePadBuilder,KeyBoardGamePad>{};


class PlateformerPhysicBuilder : public RegisterToFactory<PlateformerPhysicBuilder,PlateformerPhysic>, public Initialisable
{
public :
    virtual bool selfInitilalise(void* context);
};

class AnimatedSpriteViewBuilder : public RegisterToFactory<AnimatedSpriteViewBuilder,AnimatedSpriteView>, public Initialisable
{
public :
    virtual bool selfInitilalise(void* context);
};

#endif // _FACTORY_GLUE__


