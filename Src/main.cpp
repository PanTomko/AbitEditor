#include "Application.h"

#include <iostream>
#include <locale>
#include <codecvt>
#include <thread>

int main(int argc, char * argv[])
{
	Application app;

	if (argc > 1) 
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		app.loadBitA(converter.from_bytes(argv[1]));
	}
	app.run();

	return 0;
}