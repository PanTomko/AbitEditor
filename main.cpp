#include <iostream>

#include "Application.h"

int main()
{
	Application app;

	BitA bigBoy(173,200);
	
	bigBoy.populate(0x25bc, 2);
	bigBoy.path = "big.bitA";
	
	app.activeFile = &bigBoy;
	app.saveBitA();
	
	app.run();

	int x;
	std::cin >> x;
	//app.activeFile->marks[0][0].color = x;
	//app.saveBitA();
}