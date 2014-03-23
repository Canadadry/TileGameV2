#ifndef _JSON_HELPER_
#define _JSON_HELPER_

#include <Loader/JSON/JSONValue.h>

template<class Type>
Type getValue(const JSONObject& object, std::string name, Type defaultValue)
{
    return defaultValue;
}
template<>
int getValue(const JSONObject& object, std::string name, int defaultValue);

template<>
float getValue(const JSONObject& object, std::string name, float defaultValue);

template<>
double getValue(const JSONObject& object, std::string name, double defaultValue);


#endif //end of _JSON_HELPER_
