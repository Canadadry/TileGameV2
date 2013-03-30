/*
 * RessourceManager.h
 *
 * TileGameV2 - Copyright (c) 24 mars 2013 - Jerome Mourey
 *
 * This software is provided 'as-is', without any express or
 * implied warranty. In no event will the authors be held
 * liable for any damages arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute
 * it freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented;
 *    you must not claim that you wrote the original software.
 *    If you use this software in a product, an acknowledgment
 *    in the product documentation would be appreciated but
 *    is not required.
 * 
 * 2. Altered source versions must be plainly marked as such,
 *    and must not be misrepresented as being the original software.
 * 
 * 3. This notice may not be removed or altered from any
 *    source distribution.
 *
 *  Created on: 24 mars 2013
 */

#ifndef RESSOURCEMANAGER_H_
#define RESSOURCEMANAGER_H_
#include <string>
#include <map>

template<class T> class GenericRessourcesManager;
namespace sf{ class Texture;}

class RessourceManager
{
public:

	static void Init(std::string ressourcesDir);

	static GenericRessourcesManager<sf::Texture>& texture();
	static std::string ressourcesDir;

private:
	static GenericRessourcesManager<sf::Texture>* m_textureManager;

};



template<class T>
class GenericRessourcesManager
{
public:
	GenericRessourcesManager(){}
	virtual ~GenericRessourcesManager()
	{
		typename std::map<std::string, T*>::iterator it;
		for(it = m_ressources.begin(); it != m_ressources.end(); it++)
		{
			delete it->second;
			m_ressources.erase(it);
		}
	}


	T* load(const std::string& filename)
	{
		T* ressouce;
		if(!searchRessouces(filename,ressouce))
		{
			ressouce = createRessources(filename);
		}
		return ressouce;
	}

private:

	std::map<std::string, T*> m_ressources;

	bool searchRessouces(const std::string &filePath, T* &ressource)
	{
		typename std::map<std::string, T*>::iterator it;

		it = m_ressources.find(filePath);

		if(it == m_ressources.end())
		{
			return false;
		}
		else
		{
			ressource = it->second;
		}
		return true;
	}

	T*   createRessources(const std::string &filePath)
	{
		T* ressouce = new T;
		if(ressouce->loadFromFile(RessourceManager::ressourcesDir+filePath))
		{
			m_ressources.insert(std::pair<std::string, T*>(filePath, ressouce));
			return ressouce;
		}

		delete ressouce;
		return 0;
	}

};




#endif /* RESSOURCEMANAGER_H_ */
