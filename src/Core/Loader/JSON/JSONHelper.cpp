#include <Loader/JSON/JSONHelper.h>

static std::wstring toWide(std::string string)
{
    return std::wstring(string.begin(),string.end());
}

static std::string fromWide(std::wstring string)
{
    return std::string(string.begin(),string.end());
}

template<>
int getValue(const JSONObject& object, std::string name, int defaultValue)
{
    std::wstring wName = toWide(name);
    JSONObject::const_iterator it = object.find(wName);
    if( it == object.end() ) return defaultValue;
    if( it->second->IsNumber() == false )return defaultValue;
    return (int)it->second->AsNumber();
}
template<>
float getValue(const JSONObject& object, std::string name, float defaultValue)
{
    std::wstring wName = toWide(name);
    JSONObject::const_iterator it = object.find(wName);
    if( it == object.end() ) return defaultValue;
    if( it->second->IsNumber() == false )return defaultValue;
    return (float)it->second->AsNumber();
}
template<>
double getValue(const JSONObject& object, std::string name, double defaultValue)
{
    std::wstring wName = toWide(name);
    JSONObject::const_iterator it = object.find(wName);
    if( it == object.end() ) return defaultValue;
    if( it->second->IsNumber() == false )return defaultValue;
    return it->second->AsNumber();
}

