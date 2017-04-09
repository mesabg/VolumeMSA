#pragma once
#ifndef __CONTROL_POINT_H__
#define __CONTROL_POINT_H__

//-- Global Includes
#include <glew\glew.h>
#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm\glm\gtc\type_ptr.hpp>
#include <iostream>

//-- Using Spaces
using glm::tvec3;
using glm::tvec2;
using glm::vec2;
using std::cout;
using std::endl;

class ControlPoint {
private:
	tvec3<int> color;
	tvec2<int> position;
	const int clearance = 9;
	tvec2<int> box_x, box_y;
	unsigned int length;
	bool state;

public:
	ControlPoint(tvec2<int> position, tvec3<int> color = tvec3<double>(0,0,0), unsigned int length = 256);
	~ControlPoint();

	//-- Functions
	bool clicked(tvec2<int> position);

	//-- Getters and Setters
	void setState(bool newstate);
	bool isActive();
	tvec2<int> getPosition();
	vec2 getPositionConvertedZeroOne();
	vec2 getPositionConvertedMinusOneOne();
	tvec3<int> getColor();
	void setPosition(tvec2<double> position);
	void setX(int newX);
	void setY(int newY);
	void setColor(tvec3<int> color);
};

#endif