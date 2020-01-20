#include "SceneApp.h"

#include <iostream>
#include <codecvt>
#include <Game.h>

inline std::wstring convert(const std::string& as);

int main(int argc, char * argv[])
{
	sce::Game app;
	app.console->setFontFamily(L"Consolas");


	app.console->setBufferSize(sc::Vector2D(120, 30));
	app.console->setConsoleSize( sc::Vector2D(120, 30) );
	app.console->setBufferSize(sc::Vector2D(120, 30));
	

	app.console->showCursor(false);
	app.addScene(new SceneApp);

	if (argc > 1) 
	{
		//std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		SceneApp* wsk = (SceneApp*)app.getSceneByName(L"SceneApp"); // .loadBitA(converter.from_bytes(argv[1]));
		std::string path(argv[1]);
		wsk->canvas.loadFile(path);
	}

	app.run();

	return 0;
}

inline std::wstring convert(const std::string& as)
{
	if (as.empty()) return std::wstring();
	size_t reqLength = ::MultiByteToWideChar(CP_UTF8, 0, as.c_str(), (int)as.length(), 0, 0);
	std::wstring ret(reqLength, L'\0');
	::MultiByteToWideChar(CP_UTF8, 0, as.c_str(), (int)as.length(), &ret[0], (int)ret.length());
	return ret;
}