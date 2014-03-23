#ifndef   __BASIC_ENGINE_TYPE__
#define  __BASIC_ENGINE_TYPE__

#include <Factory/Factory.h>
#include <Engine/Entity.h>
#include <Engine/Body.h>
#include <Engine/View.h>

inline Entity* buildEntity(std::string name)
{
    //std::cout << "will buil an entity " << std::endl;
    return DerivedClassFactory<Entity>::create("EntityBuilder",(void*)name.c_str());
}

class EntityBuilder : public RegisterToFactory<EntityBuilder,Entity,Entity>, public Initialisable
{
public :
    virtual bool selfInitilalise(void* context);
};

class BodyBuilder : public RegisterToFactory<BodyBuilder,Body,Body>, public Initialisable
{
public :
    virtual bool selfInitilalise(void* context);
};

class ViewBuilder : public RegisterToFactory<ViewBuilder,View,View>{};


#endif // __BASIC_ENGINE_TYPE__


