#ifndef   __BASIC_ENGINE_TYPE__
#define  __BASIC_ENGINE_TYPE__

#include <Factory/Factory.h>
#include <Engine/Entity.h>
#include <Engine/Body.h>
#include <Engine/View.h>

class EntityBuilder : public RegisterToFactory<EntityBuilder,Entity>, public Initialisable
{
public :
    virtual bool selfInitilalise(void* context);
};

class BodyBuilder : public RegisterToFactory<BodyBuilder,Body>, public Initialisable
{
public :
    virtual bool selfInitilalise(void* context);
};

class ViewBuilder : public RegisterToFactory<ViewBuilder,View>{};


#endif // __BASIC_ENGINE_TYPE__

