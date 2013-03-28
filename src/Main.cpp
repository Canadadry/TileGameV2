#include <iostream>
#include <cmath>

#include <Engine/RessourceManager.h>
#include <Loader/INI/INIReader.h>
#include "Game/TileGame.h"

INIReader* appConf;

int main(int argc, char** argv)
{

	srand(time(NULL));
	printf("build time %s\n",__TIME__);

	std::string path = argv[0];
	path = path.substr(0,path.rfind("/"));
	path = path.substr(0,path.rfind("/"));
	path += "/Resources/";

	RessourceManager::Init(path);

	appConf = new INIReader(path+"settings.ini");

	TileGame myGame;
	Screen::mainLoop(&myGame,"TileGameV2",800,600);

	return 0;
}
