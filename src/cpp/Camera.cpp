#include <Camera.h>

void Camera::refresh() {
	this->target.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	this->target.y = sin(glm::radians(yaw));
	this->target.z = sin(glm::radians(pitch)) * cos(glm::radians(yaw));
	this->target = glm::normalize(this->target);

	//--this->view = glm::lookAt(this->position, this->position + this->target, this->up);
	this->view = glm::lookAt(this->position, this->target, this->up);
}

Camera::Camera(Transformation * player){
	this->position = vec3(0.0f, 0.0f, 20.0f);
	this->target = vec3(0.0f, 0.0f, -1.0f);
	this->up = vec3(0.0f, 1.0f, 0.0f);
	this->player = player;

	/*Setting variables*/
	this->distanceFromPlayer = 5.0f;
	this->angleAroundPlayer = 0.0f;
	this->pitch = 0.0f;
	this->yaw = 0.0f;

	this->refresh();
}

Camera::Camera(vec3 position, vec3 target, vec3 up) {
	this->position = position;
	this->target = target;
	this->up = up;
	this->refresh();
}

Camera::Camera(vec3 position, float pitch, float yaw, vec3 up){
	this->position = position;
	this->pitch = pitch;
	this->yaw = yaw;
	this->up = up;
	this->refresh();
}

Camera::~Camera() {

}

mat4 Camera::getMatrix() {
	return this->view;
}

mat4 * Camera::getView(){
	return &this->view;
}

vec3 Camera::getPosition() {
	return this->position;
}

vec3 Camera::getTarget() {
	return this->target;
}

vec3 Camera::getUp() {
	return this->up;
}

void Camera::setPosition(vec3 position) {
	this->position = position;
	this->refresh();
}

void Camera::setPositionAndTarget(vec3 position, vec3 target) {
	this->position = position;
	this->target = target;
	this->refresh();
}

void Camera::setTarget(vec3 target) {
	this->target = target;
	this->refresh();
}

void Camera::setUp(vec3 up) {
	this->up = up;
	this->refresh();
}

void Camera::setPitchYaw(float pitch, float yaw){
	this->pitch = pitch;
	this->yaw = yaw;
	this->refresh();
}

void Camera::addPosition(vec3 position) {
	this->position += position;
	this->refresh();
}

void Camera::addPositionAndTarget(vec3 position, vec3 target) {
	this->position += position;
	this->target += target;
	this->refresh();
}

void Camera::addTarget(vec3 target) {
	this->target += target;
	this->refresh();
}

void Camera::addUp(vec3 up) {
	this->up += up;
	this->refresh();
}

void Camera::bind(CGLSLProgram * shader){
	//shader->enable();
	glUniform3f(
		glGetUniformLocation(shader->getProgramID(), "u_camera_position"),
		(GLfloat)position.x,
		(GLfloat)position.y,
		(GLfloat)position.z);
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "u_view_matrix"), 1, GL_FALSE, &(this->getMatrix())[0][0]);
	//shader->disable();
}

void Camera::move(){
	this->calculateCameraPossition(this->calculateHorizontalDistance(), this->calculateVerticalDistance());
	this->yaw = 180.0f - this->angleAroundPlayer;
	this->refresh();
}

void Camera::calculateZoom(int scroll) {
	this->distanceFromPlayer -= (scroll * 0.9f);
}

void Camera::calculatePitch(int y) {
	this->pitch -= (float)y * 0.01f;
}

void Camera::calculateAngleAroundPlayer(int x) {
	this->angleAroundPlayer -= (float)x * 0.01f;
}

float Camera::calculateHorizontalDistance() {
	return this->distanceFromPlayer * glm::cos(glm::radians(this->pitch));
}

float Camera::calculateVerticalDistance() {
	return this->distanceFromPlayer * glm::sin(glm::radians(this->pitch));
}

void Camera::calculateCameraPossition(float horizontalDistance, float verticalDistance) {
	float theta = /*this->player->getRotationY() +*/ this->angleAroundPlayer;
	float offsetX = horizontalDistance * glm::sin(glm::radians(theta));
	float offsetZ = horizontalDistance * glm::cos(glm::radians(theta));

	//vec3 playerPos = vec3(0.0f);

	this->position.x = - offsetX;
	this->position.z = - offsetZ;
	this->position.y = verticalDistance;

	/*this->position.x = 0.0f - offsetX;
	this->position.z = 8.0f - offsetZ;
	this->position.y = 6.0f + verticalDistance;*/

	this->speed = 0.2f;
}