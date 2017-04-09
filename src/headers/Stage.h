#pragma once
#ifndef __STAGE_H__
#define __STAGE_H__

#include <RenderInterface.h>
#include <Reader.h>
#include <Routes.h>
#include <Light.h>
#include <Camera.h>
#include <Projection.h>
#include <RenderFacade.h>

extern vec2 getDisplaySize();

class Stage : public RenderColleague
{
private:
	//-- Singleton
	static Stage* uniqueStage;

	//-- Local Variables
	Light* light;
	Camera* camera;
	Projection* projection;
	map<string, CGLSLProgram*> *illuminationPrograms;
	float width, height;

	float* selectedModel;
	float* selectedLight;
	int* displayType;

	//-- Render Facade
	RenderFacade* renderFacade;

	//-- Button Click variables
	bool clicked;
	int xPos, yPos;
	int xPosFirst, yPosFirst;

	Stage(RenderController* renderController);
	~Stage();
	
public:
	void frontRender();

	//-- Get Instance
	static Stage* Instance(RenderController* renderController);
	static void Destroy();

	//-- Getters
	Projection* getProjection();
	Model* getSelectedModel();
	Model* getSelectedLight();
	float* getSelectedModelIndex();
	float* getSelectedLightIndex();

	//-- Shaders Initialization
	void initGLSLPrograms();

	//-- Get message
	void Notify(string message, void* data);

	//-- Functions
	void render();
};

#endif