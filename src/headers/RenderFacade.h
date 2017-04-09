#pragma once
#ifndef __RENDER_FACADE_H__
#define __RENDER_FACADE_H__

//-- Global Includes
#include <cassert>
#include <string>
#include <vector>
#include <fstream>
#include <map>

//-- Class Includes
#include <Reader.h>
#include <TransferFunction.h>

//-- Using Spaces
using std::string;
using std::vector;
using std::ifstream;
using std::map;
using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;

//-- Externs
extern unsigned int amountOfEntities;
extern unsigned int amountOfLights;
extern vec2 getDisplaySize();

class RenderFacade {
private:
	map<string, CGLSLProgram*> *shaders;

	vector<Model*> model_entities;
	vector<Model*> light_entities;

	Projection* projection;
	Camera* camera;

	string lowQualityRenderShader;
	string depthShader;

	//-- Transfer Functions
	TransferFunction* TFF8Bytes;
	TransferFunction* TFF16Bytes;

	//-- Shadow
	GLuint planeVAO, planeVBO;
	CGLSLProgram texture_program;
	glm::mat4 modelo, vista, proyeccion;

	//-- Frame buffer
	GLuint g_frameBuffer;
	GLuint g_tffTexObj;

	//-- Private functions
	void checkAssertions();
public:
	RenderFacade();
	~RenderFacade();

	//-- Initialization Methods
	void initModelEntities(
		const vector<Routes*> routes,
		const vector<Transformation*> transformations);
	//-- Init Transfer function
	GLuint initTFF1DTex(const char* filename);

	void bindProjection(Projection* projection);

	void bindCamera(Camera* camera);

	void bindShaderPrograms(map<string, CGLSLProgram*> *shaders);

	//-- Render 2D Image Based
	void render2DImageBased(string firstPass, string secondPass, string somePass, string testPass);
	void render(string shaderName);

	//-- For RayCasting
	void renderRayCasting(string firstPass, string secondPass);

	void render(Projection* projection, Camera* camera, string shaderName);

	//-- Getters
	Model* getModel(const int index);

	//-- Init Vertex Buffers
	void initVBOs();

	//-- For TTF Rendering
	void renderTTF();

	//-- ttfClicked();
	bool ttfClicked();
	TransferFunction* getTff();
};

#endif
