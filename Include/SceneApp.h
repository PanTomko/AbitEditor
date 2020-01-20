#pragma once
#include <Scene.h>
#include "Canvas.h"

class SceneApp : public sce::Scene
{
public:
	
	Canvas canvas;

	void update(float delta ) override;
	void draw(sc::Console & console) override;
	void input(sc::Event & event) override;
	void ready() override;

	SceneApp();
	~SceneApp();
};

