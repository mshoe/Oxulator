#include <iostream>
#include "CoreManager.h"



int main(int argc, char *argv[])
{
	std::cout << "Oscillation Simulator by mshoe. Version 0.001 alpha" << std::endl;
	CoreManager core;
	if (core.Init() == 0)
		return -1;


	


	core.RunLoop();
	return 0;
}