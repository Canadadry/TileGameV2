#include <Loader/JSON/JSONHelper.h>
#include <fstream>

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

template<>
std::string getValue(const JSONObject& object, std::string name, std::string defaultValue)
{
    std::wstring wName = toWide(name);
    JSONObject::const_iterator it = object.find(wName);
    if( it == object.end() ) return defaultValue;
    if( it->second->IsString() == false )return defaultValue;
    return fromWide(it->second->AsString());
}



// Helper to get a files contents
static bool get_file(std::string filename, std::wstring &data)
{
	std::wifstream in(filename.c_str());
	if (in.is_open() == false)
		return false;

	std::wstring line;
	data = L"";
	while (std::getline(in, line))
	{
		data += line;
		if (!in.eof()) data += L"\n";
	}
	return true;
}


JSONValue* JSONParseFile(std::string filename)
{
    std::wstring data;
    get_file(filename,data);

    return JSON::Parse(data.c_str());
}

