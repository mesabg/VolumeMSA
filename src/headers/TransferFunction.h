#pragma once
#ifndef __TRANSFER_FUNCTION_H__
#define __TRANSFER_FUNCTION_H__

//-- Global Includes
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <glew\glew.h>
#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm\glm\gtc\type_ptr.hpp>
#include <iostream>

//-- Classes Includes
#include <ControlPoint.h>
#include <CGLSLProgram.h>
#include <Texture.h>

//-- Using Spaces
using std::cout;
using std::endl;
using std::vector;
using std::binary_search;
using std::lower_bound;
using std::sort;
using glm::vec4;
using glm::vec2;
using glm::vec3;
using glm::mat4;

//-- Externs
extern vec2 getDisplaySize();
extern vec2 getMousePosition();
extern int getMouseLeftState();
extern int getMouseRightState();

class TransferFunction {
private:
	//-- To construct Transfer Function
	GLuint texture_unit;
	unsigned int length;
	GLint internalPixelFormat;
	GLfloat *texture_dataLinearSpline, *texture_dataCuadraticSpline, *texture_dataCubicSpline;
	vector<ControlPoint*> control_points;
	ControlPoint* controlPointSelected;
	float* color;

	//-- To paint Transfer Function
	//-- To paint Alpha Selector
	GLuint glVBO_quad_dir, glVAO_quad_dir;
	vector<GLfloat> gl_quad;
	CGLSLProgram* alpha_selector_shader;
	Texture* alpha_selector_texture;
	mat4 projection, view;
	vec2 zeroZero, oneOne;
	int lastMouseLeftState, lastMouseRightState;


	//-- Some general functions
	bool comparePoints(ControlPoint a, ControlPoint b);
	void orderPoints();
	void swap(ControlPoint** a, ControlPoint** b);

	//-- Interpolations
	float divideDifference(int x0, int x1, int fx0, int fx1);
	void linearInterpolation();
	void cuadraticInterpolation();
	void cubicInterpolations();
public:
	TransferFunction(unsigned int length = 256);
	~TransferFunction();

	void pushControlPoint(ControlPoint* controlPoint);
	bool popControlPoint(vec2 controlPointPosition);
	bool popControlPoint(unsigned int index);

	void bindLinearInterpolationTexture();
	GLuint getTextureUnit();

	//-- To paint
	float* getColor();
	bool isClicked();
	void reshape();
	void update();
	void draw();
};

#endif
