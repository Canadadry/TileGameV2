 enum{ TypeNone =0, TypeView, TypeBody, TypeGamePad, TypeComponentCount } ComponentType;

 std::map<std::string name, ComponentType> componentTypeByName({{None,TypeNone},{"View",TypeView},{"Body",TypeBody}} );


 template <int i>
 Component* build(Entity* entity,JSON* param)
 {
 	return NULL;
 }

 template <(int)TypeNone>
 Component* build(Entity* entity,JSON* param)
 {
 	return new Component(entity);
 }

 template <(int)TypeBody>
 Component* build(Entity* entity,JSON* param)
 {
 	Body* component = new Body(entity);
 	component.setSize(sf::Vector2f(param.getFloat("sizeX"),param.getFloat("sizeY")));
 	component.setOrigin(sf::Vector2f(param.getFloat("originX"),param.getFloat("originY")));
 	//component.setPosition(sf::Vector2f(param.getFloat("positionX"),param.getFloat("positionY")));
 	return component;
 }

 template <(int)TypeView>
 Component* build(Entity* entity,JSON* param)
 {
 	return new View(entity);
 }

 template <(int)TypeGamePad>
 Component* build(Entity* entity,JSON* param)
 {
 	return new GamePad(entity);
 }

Entity* buildFromJSONFile(std::string filename)
{
	Entity* entity = new Entity();
	JSON*   json = JSON(filename);
	entity.name = json->getString("name");
	entity.setView(build<componentTypeByName(json->getJSON("view").getString("type"))>(entity,json.getJSON("view")));
	entity.setBody(build<componentTypeByName(json->getJSON("body").getString("type"))>(entity,json.getJSON("body")));

	std::vector<JSON*> otherComponent = json->getArray("component");
	for(int i = 0;i<otherComponent.size;i++)
	{
			entity.addComponent(build<componentTypeByName(otherComponent[i].getString("type"))>(entity,otherComponent[i]));
	} 
	return entity;
}