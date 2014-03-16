#include <Factory/BasicType.h>
#include <Loader/JSON/JSON.h>
#include <Loader/JSON/JSONValue.h>

std::wstring toWide(std::string string)
{
    return std::wstring(string.begin(),string.end());
}

std::string fromWide(std::wstring string)
{
    return std::string(string.begin(),string.end());
}


template<class Type>
Type* buildObject(std::string name,JSONObject& context)
{
    std::wstring className    = context[toWide(name)+L"Name"]->AsString() + L"Builder";
    JSONObject*  classContext = (JSONObject*)&(context[toWide(name)+L"Context"]->AsObject());
    return DerivedClassFactory<Type>::create(fromWide(className),&classContext);
}

REGISTER_DERIVED_CLASS(EntityBuilder,Entity);

EntityBuilder::EntityBuilder()
{
}

bool EntityBuilder::selfInitilalise(void* context)
{
    if(context == NULL) return false;
    JSONObject*   jsonObject = (JSONObject*) context;
    name = (*jsonObject)[L"name"]->AsString();

    setBody(buildObject<Body>("body",*jsonObject));
    setView(buildObject<View>("view",*jsonObject));

    //    std::vector<JSON*> otherComponent = json->getArray("component");
    //    for(int i = 0;i<otherComponent.size;i++)
    //    {
    //		    entity.addComponent(build<componentTypeByName(otherComponent[i].getString("type"))>(entity,otherComponent[i]));
    //    }
    //    return entity;
    return true;
}

REGISTER_DERIVED_CLASS(BodyBuilder,Body);

BodyBuilder::BodyBuilder()
{
}

bool BodyBuilder::selfInitilalise(void* context)
{
    if(context == NULL) return false;
    JSONObject*   jsonObject = (JSONObject*) context;

    setSize(sf::Vector2f( (*jsonObject)[L"sizeX"]->AsNumber() , (*jsonObject)[L"sizeY"]->AsNumber() ));
    setOrigin(sf::Vector2f( (*jsonObject)[L"originX"]->AsNumber() , (*jsonObject)[L"originY"]->AsNumber() ));

    return true;
}

REGISTER_DERIVED_CLASS(ViewBuilder,View);

ViewBuilder::ViewBuilder()
{
}

bool ViewBuilder::selfInitilalise(void* context)
{
//    if(context == NULL) return false;
//    JSONObject*   jsonObject = (JSONObject*) context;

    return true;
}
