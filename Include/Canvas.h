#pragma once
#include <BitA.h>
#include <Console.h>

class Canvas{
public:

	//void setPossition(const sc::Vector2D & possition);
	
	bool isOnCanvas(const sc::Vector2D & vec);
	bool loadFile(const std::string & path);

	void update(float delta);
	void draw(sc::Console & console);
	void input(sc::Event & evenet);

	Canvas();
	~Canvas();
private:

	void drawFile(sc::Console & console);
	void drawBorder(sc::Console & console);
	

	sc::BitA<sc::WMark>* file;

	sc::Vector2D posssition;
	sc::Vector2D fileDrawPossition;
	sc::Vector2D fileOffSet;
	sc::Vector2D drawMaxSize;
	sc::Vector2D size;
};

