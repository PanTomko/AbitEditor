#include "SceneApp.h"
#include "ToolsManager.h"

SceneApp::SceneApp(){
	name = L"SceneApp";
}

SceneApp::~SceneApp(){
	ToolsManager::toolsManager->app = this;
}

void SceneApp::ready(){
}

void SceneApp::update(float delta){
	canvas.update(delta);
	ToolsManager::toolsManager->update(delta);
}

void SceneApp::draw(sc::Console & console){
	canvas.draw(console);
	ToolsManager::toolsManager->draw(console);
}

void SceneApp::input(sc::Event & event){
	canvas.input(event);
	ToolsManager::toolsManager->input(event);
}




