#pragma once
#ifndef __READER_H_
#define __READER_H_

// -- Global Includes
#include <cstdio>

// -- Class Includes
#include <Model.h>

// -- Using Spaces
using std::cout;
using std::endl;

class Reader : public Model{
private:

public:
	Reader(Routes* routes);
	~Reader();

	GLuint initVol3DTex(const char* filename, GLuint w, GLuint h, GLuint d);
};

#endif