#include <iostream>
#include <cmath>

#include <Graphics/RessourceManager.h>
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
	path = path.substr(0,path.rfind("/"));
	path += "/Resources/";

	RessourceManager::Init(path);

	appConf = new INIReader(path+"settings.ini");

	Screen::mainLoop(new TileGame(320,240),"TileGameV2",320,240);

	return 0;
}
