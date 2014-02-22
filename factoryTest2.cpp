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
 	return Component::build(entity,param);
 }

 template <(int)TypeBody>
 Component* build(Entity* entity,JSON* param)
 {
 	return Body::build(entity,param);
 }

 template <(int)TypeView>
 Component* build(Entity* entity,JSON* param)
 {
  	return View::build(entity,param);
  }

 template <(int)TypeGamePad>
 Component* build(Entity* entity,JSON* param)
 {
  	return GamePad::build(entity,param);
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