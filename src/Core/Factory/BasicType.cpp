#include <Factory/BasicType.h>
#include <Loader/JSON/JSON.h>
#include <Loader/JSON/JSONValue.h>
#include <iostream>
#include <fstream>
#include <Graphics/RessourceManager.h>

#include <Engine/Physics.h>
#include <Engine/GamePad.h>

static std::wstring toWide(std::string string)
{
    return std::wstring(string.begin(),string.end());
}

static std::string fromWide(std::wstring string)
{
    return std::string(string.begin(),string.end());
}


// Helper to get a files contents
bool get_file(std::string filename, std::wstring &data)
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


template<class Type>
Type* buildObject(std::string name,JSONObject& context)
{
    std::wstring sectionName = toWide(name)+L"Name";
    std::wstring sectionContext = toWide(name)+L"Context";
    //std::cerr << "  trying to build component " << name << std::endl;

    if(context.find(sectionName) == context.end())
    {
	//std::cerr<<"        " << name << "Name not found" << std::endl;
	return NULL;
    }
    if(context.find(sectionContext)== context.end())
    {
	//std::cerr<<"        " << name << "Context not found" << std::endl;
	return NULL;
    }
    if(context.find(sectionContext)->second->IsObject() == false)
    {
	//std::cerr<<"        " << name << "Context not an object" << std::endl;
	return NULL;
    }
    std::wstring className    = context[sectionName]->AsString() + L"Builder";
    JSONObject*  classContext = (JSONObject*)&(context[sectionContext]->AsObject());

    Type* object = DerivedClassFactory<Type>::create(fromWide(className),classContext);

    //std::cerr << "  Has to build component" << name << " of class " << fromWide(className) << " : " << (long long)object << std::endl;

    return object;

}

REGISTER_DERIVED_CLASS(EntityBuilder,Entity);
bool EntityBuilder::selfInitilalise(void* context)
{
    if(context == NULL) return false;
    std::wstring data;
    std::string filename = RessourceManager::ressourcesDir+"Entity/"+std::string((char*)context)+".json";
    get_file(filename,data);

    //std::cerr << " parsing json file("<< filename << ")" << std::endl;


    JSONValue*   parseResult = JSON::Parse(data.c_str());
    if(parseResult == NULL )
    {
	std::cerr << "Error while parsing file "<< filename << std::endl;
	return false;
    }
    JSONObject   jsonObject = parseResult->AsObject();
    name = jsonObject[L"name"]->AsString();

    //std::cerr << "building entity " << (char*) context << " with name " << fromWide(name) << std::endl;

    setBody(buildObject<Body>("body",jsonObject));
    setView(buildObject<View>("view",jsonObject));
    setPhysics(buildObject<Physics>("physics",jsonObject));
    setGamepad(buildObject<GamePad>("gamepad",jsonObject));

    //std::cerr <<"build done"  << std::endl;

    return true;
}


REGISTER_DERIVED_CLASS(BodyBuilder,Body);
bool BodyBuilder::selfInitilalise(void* context)
{
    if(context == NULL) return false;
    JSONObject&   jsonObject = *(JSONObject*) context;

    setSize(sf::Vector2f( jsonObject[L"sizeX"]->AsNumber() , jsonObject[L"sizeY"]->AsNumber() ));
    setOrigin(sf::Vector2f( jsonObject[L"originX"]->AsNumber() , jsonObject[L"originY"]->AsNumber() ));
    return true;
}

REGISTER_DERIVED_CLASS(ViewBuilder,View);

