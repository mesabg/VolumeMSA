#pragma once
#ifndef __SIDE_BAR_H_
#define __SIDE_BAR_H_

//-- Global Includes
#include <AntTweakBar.h>
//-- Class Includes
#include <RenderInterface.h>
#include <Model.h>

//-- Using Spaces
using std::vector;
using glm::vec3;
using glm::vec4;
using glm::mat4;

typedef enum { IMAGE2DBASED, IMAGE3DBASED, RAYCASTING } DisplayType;
typedef enum { LINEAR, CUADRATIC, CUBIC } InterpolationType;

class SideBar : public RenderColleague {
private:
	//-- Singlenton instance
	static SideBar *uniqueSideBar;

	//-- Bars
	TwBar* principalPropertiesBar;
	TwBar* modelPropertiesBar;
	TwBar* lightPropertiesBar;

	//-- Properties to edit
	Model* model;
	float* selectedModel;
	float* selectedLight;
	float* tffColor;

	//-- Variables
	unsigned int showType;
	bool* showShadowMap;


	//--
	const int n_models = 1;

	//-- Show types
	void clear();
	void principalView();
	void modelView();
	void lightView();

	DisplayType displayMode = IMAGE2DBASED;
	TwEnumVal displayTypeSelector[3];
	TwType displayType;

	InterpolationType interpolationMode = LINEAR;
	TwEnumVal interpolationTypeSelector[3];
	TwType interpolationType;

	//-- Constructors
	SideBar(RenderController* renderController);
	SideBar(RenderController* renderController, const int width, const int height);
	~SideBar();
public:
	//-- Singleton Design Pattern
	static SideBar* Instance(RenderController* renderController);
	static SideBar* Instance(RenderController* renderController, const int width, const int height);
	static void Destroy();

	//-- @Override Mediator design pattern
	void Notify(string message, void* data);

	//-- Setters
	void setModel(Model* model);
	void setSelectModelTarget(float *target);
	void setSelectLightTarget(float *target);
	void setTffColor(float* fttColor);

	//-- Some Functions
	void reshape(int gWidth, int gHeight);
	void recalculateTransformationMatrices();
	void bindPrincipal();
	void bindModel();
	void bindLight();
	void bindLightWithModel();
	void recalculateLight();
	void update();

	//-- Callbacks
	void selectModelCall();
	void selectLightCall();
	void doneCall();
	void textureCall();
	void selectPhongCall();
	void selectBlinnPhongCall();
	void selectOrenNayarCall();
	void selectCookTorranceCall();
	void selectPerFragmentLightningCall();
	void selectPerVertexLightningCall();
	void activeLightsCall();
	void animateCall();
	void updatePrincipal();
};

//-- Tweakbar Callbacks
void TW_CALL selectModelCallback(void *clientData);
void TW_CALL selectLightCallback(void *clientData);
void TW_CALL doneCallback(void *clientData);
void TW_CALL textureCallback(void *clientData);
void TW_CALL selectPhongCallback(void *clientData);
void TW_CALL selectBlinnPhongCallback(void *clientData);
void TW_CALL selectOrenNayarCallback(void *clientData);
void TW_CALL selectCookTorranceCallback(void *clientData);
void TW_CALL selectPerFragmentLightningCallback(void *clientData);
void TW_CALL selectPerVertexLightningCallback(void *clientData);
void TW_CALL activeLightsCallback(void *clientData);
void TW_CALL animateCallback(void *clientData);


#endif
