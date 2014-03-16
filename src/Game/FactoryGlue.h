#ifndef   _FACTORY_GLUE__
#define  _FACTORY_GLUE__

#include <Factory/Factory.h>

#include "AnimatedSpriteView.h"
#include "BasicIA.h"
#include "KeyBoardGamePad.h"
#include "PlateformerPhysic.h"

class BasicIABuilder : public RegisterToFactory<BasicIA,GamePad>{};

class KeyBoardGamePadBuilder : public RegisterToFactory<KeyBoardGamePad,GamePad>{};


class PlateformerPhysicBuilder : public RegisterToFactory<PlateformerPhysic,Physics>, public Initialisable
{
public :
    virtual bool selfInitilalise(void* context);
};

class AnimatedSpriteViewBuilder : public RegisterToFactory<AnimatedSpriteView,View>, public Initialisable
{
public :
    virtual bool selfInitilalise(void* context);
};

#endif // _FACTORY_GLUE__


