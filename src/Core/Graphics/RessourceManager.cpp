/*
 * RessourceManager.cpp
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

#include "RessourceManager.h"
#include <SFML/Graphics/Texture.hpp>

void RessourceManager::Init(std::string ressourcesDir)
{
	 if(m_textureManager == 0)
	 {
		 RessourceManager::ressourcesDir = ressourcesDir;
		 m_textureManager =  new GenericRessourcesManager<sf::Texture>();
	 }
	 else
	 {
		 printf("Be carrefull you have already initialised the RessourceManager.\n");
	 }
}

GenericRessourcesManager<sf::Texture>& RessourceManager::texture()
 {
	 if(m_textureManager == 0)
	 {
		 Init("");
		 printf("You should initialised the RessourceManager before using it.\n");
	 }
	 return *m_textureManager;
 }

 std::string RessourceManager::ressourcesDir = "";
 GenericRessourcesManager<sf::Texture>* RessourceManager::m_textureManager = 0;


