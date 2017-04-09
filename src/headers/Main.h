#pragma once
#ifndef __MAIN_H_
#define __MAIN_H_
#include <ConcreteRenderController.h>

//-- Global Functions
float getFrameTimeSeconds();
vec2 getMousePosition();
int getMouseLeftState();
int getMouseRightState();
vec2 getDisplaySize();
int checkForOpenGLError(const char* file, int line);

#endif