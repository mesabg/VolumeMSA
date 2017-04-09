#pragma once
#ifndef __ROUTES_H__
#define __ROUTES_H__

#include <string>
#include <vector>

using std::string;
using std::vector;

class Routes {
public:
	//-- Variables
	string raw_model;
	int width;
	int height;
	int depth;
	int bytes;

	Routes(string raw_model, int width = 256, int height = 256, int depth = 256, int bytes = 1);
	
	~Routes();
};

#endif
