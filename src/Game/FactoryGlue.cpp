#include <Loader/JSON/JSON.h>
#include <Loader/JSON/JSONValue.h>
#include <Loader/JSON/JSONHelper.h>

#include "FactoryGlue.h"

#include <Graphics/RessourceManager.h>

#include <iostream>

static std::wstring toWide(std::string string)
{
    return std::wstring(string.begin(),string.end());
}

static std::string fromWide(std::wstring string)
{
    return std::string(string.begin(),string.end());
}


REGISTER_DERIVED_CLASS(BasicIABuilder,GamePad);

REGISTER_DERIVED_CLASS(KeyBoardGamePadBuilder,GamePad);

REGISTER_DERIVED_CLASS(PlateformerPhysicBuilder,Physics);

bool PlateformerPhysicBuilder::selfInitilalise(void* context)
{
    if(context == NULL) return false;
    JSONObject&   jsonObject = *(JSONObject*) context;

    gravity           = sf::Vector2f( getValue<float>(jsonObject,"gravityX",0.0f),getValue<float>(jsonObject,"gravityY",0.0f) );
    max_speed         = sf::Vector2f( getValue<float>(jsonObject,"maxSpeedX",0.0f),getValue<float>(jsonObject,"maxSpeedY",0.0f));
    jump_power        = getValue<float>(jsonObject,"jumpPower",0.0f);
    walk_speed        = getValue<float>(jsonObject,"walkSpeed",0.0f);
    run_speed         = getValue<float>(jsonObject,"runSpeed",0.0f);
    walk_deceleration = getValue<float>(jsonObject,"walkDeceleration",0.0f);

    std::cout << "gravity ("<<gravity.x<<","<<gravity.y<<")" << std::endl;


    return true;
}

REGISTER_DERIVED_CLASS(AnimatedSpriteViewBuilder,View);
bool AnimatedSpriteViewBuilder::selfInitilalise(void* context)
{
    if(context == NULL) return false;
    JSONObject*   jsonObject = (JSONObject*) context;

    buildAnimFromFile(RessourceManager::ressourcesDir+"/"+fromWide((*jsonObject)[L"animationFile"]->AsString()));

    return true;
}

