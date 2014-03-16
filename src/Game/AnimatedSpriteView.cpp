#include "AnimatedSpriteView.h"

#include <Graphics/AnimatedTile.h>
#include <Graphics/RessourceManager.h>

#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

AnimatedSpriteView::AnimatedSpriteView()
    : View()
    , m_sprite(new AnimatedTile)
    , m_anim_count(0)
{
    drawable = m_sprite;
}

AnimatedSpriteView::AnimatedSpriteView(std::string descriptionFile)
    : View()
    , m_sprite(new AnimatedTile)
    , m_anim_count(0)
{
    drawable = m_sprite;
    buildAnimFromFile(RessourceManager::ressourcesDir+"/"+descriptionFile);
}

AnimatedSpriteView::~AnimatedSpriteView()
{
    delete m_sprite;
}

void AnimatedSpriteView::update()
{
    View::update();
    m_sprite->update();
}


void AnimatedSpriteView::useAnim(unsigned int index)
{
    if(index>= m_anim_count) return;
    m_sprite->useAnim(index);
}

unsigned int AnimatedSpriteView::animCount() const{return m_anim_count;}

std::vector<int> split(const std::string &s, char delim)
{
    std::stringstream ss(s);
    std::string item;
    std::vector<int> elems;
    while (std::getline(ss, item, delim))
    {
	elems.push_back(atoi(item.c_str()));
    }
    return elems;
}

void AnimatedSpriteView::buildAnimFromFile(std::string filename)
{
    std::ifstream file(filename, std::ios::in);
    if(file)
    {
	std::string name;
	int tileset_width,tileset_height, origin_x,origin_y;
	file >> name;
	file >> tileset_width;
	file >> tileset_height;
	file >> origin_x;
	file >> origin_y;

	sf::Texture* tileset = RessourceManager::texture().load("/"+name);
	m_sprite->setTileSet(*tileset,tileset_width,tileset_height);
	m_sprite->setOrigin(origin_x,origin_y);



//	std::cout <<"reading file " << filename <<std::endl;
//	std::cout << name << " " << tileset_width << " " << tileset_height << " " <<origin_x << " " <<origin_y << std::endl;

	std::vector<int> anim ;
	while(!file.eof())
	{
	    std::string uselessName;
	    file >> uselessName;
	    if(uselessName =="") break;
	    std::string lineToSplit;
	    std::getline(file,lineToSplit);
	 //   std::cout <<uselessName<<" "<< lineToSplit << std::endl;
	    std::vector<int> splited = split(lineToSplit,' ');
	    std::vector<int> anime;

//	    std::cout << uselessName << " ";
	    std::vector<int>::iterator it = splited.begin();
//	    while(it != splited.end())
//	    {
//		std::cout << (*it) << " ";
//		it++;
//	    }

//	    std::cout <<std::endl;
	    anim.assign(splited.begin()+2,splited.end());
	    m_sprite->appendAnimDesc(anim,splited[1]);
	    m_anim_count++;

	}
	m_sprite->useAnim(0);

	file.close();
    }
    else{
	std::cout << "can't read animation file "<<filename;
    }

}
