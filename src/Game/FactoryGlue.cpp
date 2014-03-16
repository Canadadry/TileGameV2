#include <Loader/JSON/JSON.h>
#include <Loader/JSON/JSONValue.h>

#include "FactoryGlue.h"

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
    JSONObject*   jsonObject = (JSONObject*) context;

    gravity           = sf::Vector2f( (*jsonObject)[L"gavityX"]->AsNumber()   , (*jsonObject)[L"gravityY"]->AsNumber() );
    max_speed         = sf::Vector2f( (*jsonObject)[L"maxSpeedX"]->AsNumber() , (*jsonObject)[L"maxSpeedY"]->AsNumber() );
    jump_power        = (*jsonObject)[L"jumpPower"]->AsNumber();
    walk_speed        = (*jsonObject)[L"walkSpeed"]->AsNumber();
    run_speed         = (*jsonObject)[L"runSpeed"]->AsNumber();
    walk_deceleration = (*jsonObject)[L"walkDeceleration"]->AsNumber();

    return true;
}

REGISTER_DERIVED_CLASS(AnimatedSpriteViewBuilder,View);
bool AnimatedSpriteViewBuilder::selfInitilalise(void* context)
{
    if(context == NULL) return false;
    JSONObject*   jsonObject = (JSONObject*) context;

    buildAnimFromFile(fromWide((*jsonObject)[L"animationFile"]->AsString()));

    return true;
}

