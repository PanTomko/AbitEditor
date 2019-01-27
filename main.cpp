#include <iostream>
#include <locale>
#include <codecvt>

#include "Application.h"

int main(int argc, char * argv[])
{
	Application app;
	app.drawLaout();
	app.toolManadger.draw();

	if (argc > 1)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring d = converter.from_bytes(argv[1]);
		app.loadBitA(d);
	}

	app.run();

	return 0;
}