#include "Canvas.h"

#include <math.h>

Canvas::Canvas(){
}

Canvas::~Canvas(){
	if (file != nullptr)
		delete file;
}

void Canvas::update(float delta){
}

void Canvas::draw(sc::Console & console){
	if (file != nullptr) {
		drawBorder(console);
		drawFile(console);
	}
}

void Canvas::input(sc::Event & evenet){
}

bool Canvas::loadFile(const std::string & path){
	if (file != nullptr)
		delete file;

	file = new sc::BitA<sc::WMark>(path);
	fileOffSet = sc::Vector2D{ 0,0 };
	
	if (file->size_x >= size.x){
		drawMaxSize.x = size.x;
		fileDrawPossition.x = posssition.x;
		
	}
	else{
		drawMaxSize.x = file->size_x;
		fileDrawPossition.x = static_cast<int>(std::floor((82 / 2) - (drawMaxSize.x / 2)));
	}

	if (file->size_y >= size.y){
		drawMaxSize.y = size.y;
		fileDrawPossition.y = posssition.y;

	}
	else{
		drawMaxSize.y = file->size_y;
		fileDrawPossition.y = static_cast<int>(std::floor((82 / 2) - (drawMaxSize.y / 2)));
	}

	return false;
}

bool Canvas::isOnCanvas(const sc::Vector2D & vec){
	// Testing X
	if (vec.x >= fileDrawPossition.x && vec.x < fileDrawPossition.x + file->size_x) {
	}
	else return false;

	// Testing Y
	if (vec.y >= fileDrawPossition.y && vec.y < fileDrawPossition.y + file->size_y) {
	}
	else return false;

	return true;
}

void Canvas::drawFile(sc::Console & console){
	console.draw(*file, fileDrawPossition, fileOffSet, drawMaxSize + fileOffSet);
}

void Canvas::drawBorder(sc::Console & console){
}


