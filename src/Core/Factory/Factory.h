#ifndef _FACTORY_HPP_
#define _FACTORY_HPP_

#include <map>
#include <string>


class Initialisable
{
public:
    virtual bool selfInitilalise(void* context = NULL) =0;
};


//default baseClass
class Object{
public:
    virtual ~Object(){};
};

// provide a simple create function to derived classes
template<class DerivedClass, class BaseClass = Object>
class RegisterToFactory : public DerivedClass
{
public:
    static BaseClass* create()
    {
	return new DerivedClass();
    }
};

template<class BaseClass>
class DerivedClassFactory
{

public:
    static DerivedClassFactory* instance()
    {
	static DerivedClassFactory* __self = NULL;
	if (__self == NULL)
	    __self = new DerivedClassFactory();

	return __self;
    }

    bool reg(const std::string& id,  BaseClass* (*creator)() )
    {
//	std::cout << "register type " << id << " with function creator "<< (long long)creator << "\n";
	creators_factory[id] = creator;
	return true;
    }

    // pass in creator function pointer to register it to id
    static BaseClass* create(const std::string& id, void* context = NULL)
    {
	if(instance()->creators_factory[id] == NULL) return NULL;
	BaseClass* object =  instance()->creators_factory[id]();
	Initialisable* initialisable = dynamic_cast<Initialisable*>(object);
	if(initialisable != NULL) initialisable->selfInitilalise(context);
	return object;
    }
private:
    std::map<std::string, BaseClass* (*)()> creators_factory;

};

typedef DerivedClassFactory<Object> ObjectFactory;

#define REGISTER_OBJECT(T) REGISTER_DERIVED_CLASS(T,Object)
#define REGISTER_DERIVED_CLASS(DerivedClass, BaseClass) bool isRegistered_##DerivedClass##BaseClass =  DerivedClassFactory<BaseClass>::instance()->reg(#DerivedClass, DerivedClass::create)

#endif // _FACTORY_HPP_

//	//Example of use, uncomment to try it
//
//      //========================================================================================
//
//      // Start by creating a simple class that inherits from the helper template, then call a macro
//
//	class StandardObject : public RegisterToFactory<StandardObject> { public : StandardObject() { std::cout << "StandardObject constructor\n"; } };
//	REGISTER_OBJECT(StandardObject);
//
//      //========================================================================================
//
//      // Sometimes you need to initialise your class, if you need so,
//      // inherits also form Initialisable class then implement the selfInitilalise function
//
//	class InitialisableObject : public RegisterToFactory<InitialisableObject>, public Initialisable
//	{
//	public :
//	    InitialisableObject() { std::cout << "InitialisableObject constructor\n"; }
//	    virtual bool selfInitilalise(void* context) {	 std::cout << "InitialisableObject initialised " << (long long) context <<"\n"; return  true;    }
//	};
//	REGISTER_OBJECT(InitialisableObject);
//
//      //========================================================================================
//
//      // if you need to inherit form a special class add it to the template parameter
//      // don't forget to call another macro
//
//	class BaseObject{ public: virtual ~BaseObject(){}; };
//	class DerivedObject : public RegisterToFactory<DerivedObject,BaseObject> { public : DerivedObject() { std::cout << "DerivedObject constructor\n"; } };
//	REGISTER_DERIVED_CLASS(DerivedObject,BaseObject);
//
//      //========================================================================================
//
//      // You can do both intialisation and inheritance
//
//	class InitialisableDerivedObject : public RegisterToFactory<InitialisableDerivedObject,BaseObject>, public Initialisable
//	{
//	public :
//	    InitialisableDerivedObject() { std::cout << "InitialisableDerivedObject constructor\n"; }
//	    virtual bool selfInitilalise(void* context) {	 std::cout << "InitialisableDerivedObject initialised " << (long long) context <<"\n"; return  true;    }
//	};
//	REGISTER_DERIVED_CLASS(InitialisableDerivedObject,BaseObject);
//
//      //========================================================================================
//
//      // Now you just have to call the factory.
//      // Be cautionous, the factory depend on the base class you choose
//
//	int main(void)
//	{
//	    int context = 0;
//	    delete ObjectFactory::create("InitialisableObject",&context);
//	    delete ObjectFactory::create("StandardObject");
//	    delete DerivedClassFactory<BaseObject>::create("DerivedObject");
//	    delete DerivedClassFactory<BaseObject>::create("InitialisableDerivedObject",&context);
//	    return 0;
//	}
