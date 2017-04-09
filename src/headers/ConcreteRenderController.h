#pragma once
#ifndef __CONCRETE_RENDER_CONTROLLER_H_
#define __CONCRETE_RENDER_CONTROLLER_H_

//-- Class Includes
#include <RenderInterface.h>
#include <GUI.h>
#include <Stage.h>
#include <SideBar.h>

class ConcreteRenderController : public RenderController
{
private:
	//-- All Instances of Colleagues
	Stage* stage;
	GUI* gui;
	SideBar* sideBar;

	//-- Functions
	void render();
public:
	static double lastFrameTime;
	static double delta;
	static double getCurrentTime();
	static double getFrameTimeSeconds();

	ConcreteRenderController(int width = 1440, int height = 990);
	~ConcreteRenderController();

	//-- Override
	void Send(string message, void* data, RenderColleague* colleague);

	//-- Play and Pause
	int finish();
	int infinity();
};

#endif