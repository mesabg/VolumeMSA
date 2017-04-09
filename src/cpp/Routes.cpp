#include <Routes.h>

Routes::Routes(string raw_model, int width, int height, int depth, int bytes):
	raw_model(raw_model),
	width(width),
	height(height),
	depth(depth),
	bytes(bytes){}

Routes::~Routes() {
	this->raw_model.~basic_string();
}
