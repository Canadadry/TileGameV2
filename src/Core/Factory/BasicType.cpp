#include <Factory/BasicType.h>
#include <Loader/JSON/JSON.h>
#include <Loader/JSON/JSONValue.h>

static std::wstring toWide(std::string string)
{
    return std::wstring(string.begin(),string.end());
}

static std::string fromWide(std::wstring string)
{
    return std::string(string.begin(),string.end());
}


//// Helper to get a files contents
//bool get_file(std::string filename, std::wstring &data)
//{
//	std::wifstream in(filename.c_str());
//	if (in.is_open() == false)
//		return false;

//	std::wstring line;
//	data = L"";
//	while (std::getline(in, line))
//	{
//		data += line;
//		if (!in.eof()) data += L"\n";
//	}
//	return true;
//}


template<class Type>
Type* buildObject(std::string name,JSONObject& context)
{
    std::wstring className    = context[toWide(name)+L"Name"]->AsString() + L"Builder";
    JSONObject*  classContext = (JSONObject*)&(context[toWide(name)+L"Context"]->AsObject());
    return DerivedClassFactory<Type>::create(fromWide(className),&classContext);
}

REGISTER_DERIVED_CLASS(EntityBuilder,Entity);
bool EntityBuilder::selfInitilalise(void* context)
{
    if(context == NULL) return false;
//    JSON json; std::wstring data;
//    get_file("Entity/"+std::string((char*)context),data);
//    JSONObject&   jsonObject = json.Parse(data)->AsObject();
//    name = jsonObject[L"name"]->AsString();

//    setBody(buildObject<Body>("body",jsonObject));
//    setView(buildObject<View>("view",jsonObject));
//    setView(buildObject<Physics>("physics",*jsonObject));
//    setView(buildObject<gamepad>("gamepad",*jsonObject));

    return true;
}

REGISTER_DERIVED_CLASS(BodyBuilder,Body);
bool BodyBuilder::selfInitilalise(void* context)
{
    if(context == NULL) return false;
    JSONObject*   jsonObject = (JSONObject*) context;

    setSize(sf::Vector2f( (*jsonObject)[L"sizeX"]->AsNumber() , (*jsonObject)[L"sizeY"]->AsNumber() ));
    setOrigin(sf::Vector2f( (*jsonObject)[L"originX"]->AsNumber() , (*jsonObject)[L"originY"]->AsNumber() ));

    return true;
}

REGISTER_DERIVED_CLASS(ViewBuilder,View);

