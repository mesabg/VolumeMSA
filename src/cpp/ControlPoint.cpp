#include <ControlPoint.h>

ControlPoint::ControlPoint(tvec2<int> position, tvec3<int> color, unsigned int length):position(position), color(color), length(length){
	//-- x Limits
	box_x.x = position.x - clearance >= 0 ? position.x - clearance : 0;
	box_x.y = position.x + clearance <= length ? position.x + clearance : length;

	//-- y Limits
	box_y.x = position.y - clearance >= 0 ? position.y - clearance : 0;
	box_y.y = position.y + clearance <= length ? position.y + clearance : length;

	//-- default state
	state = false;
}

ControlPoint::~ControlPoint(){}

bool ControlPoint::clicked(tvec2<int> position){
	return 
		position.x >= box_x.x && 
		position.x <= box_x.y &&
		position.y >= box_y.x && 
		position.y <= box_y.y;
}

void ControlPoint::setState(bool newstate){
	this->state = newstate;
}

bool ControlPoint::isActive(){
	return state;
}

tvec2<int> ControlPoint::getPosition(){
	return this->position;
}

vec2 ControlPoint::getPositionConvertedZeroOne(){
	return vec2(float(position.x) / float(length - 1), float(position.y) / float(length - 1));
}

vec2 ControlPoint::getPositionConvertedMinusOneOne() {
	vec2 point = vec2(float(position.x) / float(length - 1), float(position.y) / float(length - 1));
	return vec2(point.x, point.y);
}

tvec3<int> ControlPoint::getColor(){
	return this->color;
}

void ControlPoint::setPosition(tvec2<double> position){
	this->position = position;
}

void ControlPoint::setX(int newX){
	this->position.x = newX;
}

void ControlPoint::setY(int newY) {
	this->position.y = newY;
}

void ControlPoint::setColor(tvec3<int> color){
	this->color = color;
}
