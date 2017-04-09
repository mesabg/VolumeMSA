#include <Model.h>
#include <iostream>

void Model::drawElements(){
	// -- VBO Data
	glBindBuffer(GL_ARRAY_BUFFER, this->glVBO_dir);
	// -- Vertex 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), 0);
	// -- Normals								
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));//6
	// -- Texture Coord								
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));//3
	//-- Tangents								
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (void*)(9 * sizeof(GLfloat)));//9

	// -- Drawing
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->glVBO_indexes_dir);

	glDrawElements(GL_TRIANGLES, this->glVBO_indexes_size, GL_UNSIGNED_INT, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(0);
}

void Model::generateCube(GLfloat SIZE){
	glCubeVertices = {
		-SIZE, SIZE, -SIZE, 0, 1, 0,
		-SIZE, -SIZE, -SIZE, 0, 0, 0,
		SIZE, -SIZE, -SIZE, 1, 0, 0,
		SIZE, -SIZE, -SIZE, 1, 0, 0,
		SIZE, SIZE, -SIZE, 1, 1, 0,
		-SIZE, SIZE, -SIZE, 0, 1, 0,

		-SIZE, -SIZE, SIZE, 0, 0, 1,
		-SIZE, -SIZE, -SIZE, 0, 0, 0,
		-SIZE, SIZE, -SIZE, 0, 1, 0,
		-SIZE, SIZE, -SIZE, 0, 1, 0,
		-SIZE, SIZE, SIZE, 0, 1, 1,
		-SIZE, -SIZE, SIZE, 0, 0, 1,

		SIZE, -SIZE, -SIZE, 1, 0, 0,
		SIZE, -SIZE, SIZE, 1, 0, 1,
		SIZE, SIZE, SIZE, 1, 1, 1,
		SIZE, SIZE, SIZE, 1, 1, 1,
		SIZE, SIZE, -SIZE, 1, 1, 0,
		SIZE, -SIZE, -SIZE, 1, 0, 0,

		-SIZE, -SIZE, SIZE, 0, 0, 1,
		-SIZE, SIZE, SIZE, 0, 1, 1,
		SIZE, SIZE, SIZE, 1, 1, 1,
		SIZE, SIZE, SIZE, 1, 1, 1,
		SIZE, -SIZE, SIZE, 1, 0, 1,
		-SIZE, -SIZE, SIZE, 0, 0, 1,

		-SIZE, SIZE, -SIZE, 0, 1, 0,
		SIZE, SIZE, -SIZE, 1, 1, 0,
		SIZE, SIZE, SIZE, 1, 1, 1,
		SIZE, SIZE, SIZE, 1, 1, 1,
		-SIZE, SIZE, SIZE, 0, 1, 1,
		-SIZE, SIZE, -SIZE, 0, 1, 0,

		-SIZE, -SIZE, -SIZE, 0, 0, 0,
		-SIZE, -SIZE, SIZE, 0, 0, 1,
		SIZE, -SIZE, -SIZE, 1, 0, 0,
		SIZE, -SIZE, -SIZE, 1, 0, 0,
		-SIZE, -SIZE, SIZE, 0, 0, 1, 
		SIZE, -SIZE, SIZE, 1, 0, 1 };

	/*glCubeVertices = {
		0, 1, 0, 0, 1, 0,
		0, 0, 0, 0, 0, 0,
		1, 0, 0, 1, 0, 0,
		1, 0, 0, 1, 0, 0,
		1, 1, 0, 1, 1, 0,
		0, 1, 0, 0, 1, 0,

		0, 0, 1, 0, 0, 1,
		0, 0, 0, 0, 0, 0,
		0, 1, 0, 0, 1, 0,
		0, 1, 0, 0, 1, 0,
		0, 1, 1, 0, 1, 1,
		0, 0, 1, 0, 0, 1,

		1, 0, 0, 1, 0, 0,
		1, 0, 1, 1, 0, 1,
		1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1,
		1, 1, 0, 1, 1, 0,
		1, 0, 0, 1, 0, 0,

		0, 0, 1, 0, 0, 1,
		0, 1, 1, 0, 1, 1,
		1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1,
		1, 0, 1, 1, 0, 1,
		0, 0, 1, 0, 0, 1,

		0, 1, 0, 0, 1, 0,
		1, 1, 0, 1, 1, 0,
		1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1,
		0, 1, 1, 0, 1, 1,
		0, 1, 0, 0, 1, 0,

		0, 0, 0, 0, 0, 0,
		0, 0, 1, 0, 0, 1,
		1, 0, 0, 1, 0, 0,
		1, 0, 0, 1, 0, 0,
		0, 0, 1, 0, 0, 1,
		1, 0, 1, 1, 0, 1 };*/
}

Model::Model() {
	/*Init Tranformation*/
	this->transformation = new Transformation();

	/*Init Material Colors*/
	this->light = new Light();
}

Model::Model(Routes* routes):routes(routes){
	//-- Init Tranformation
	this->transformation = NULL;

	//-- Init Material Colors
	this->light = NULL;

	//-- Init Quad
	//-- For 2D Image Based Rendering
	float size = 1.0f;
	this->glVBO_quad = {
		 size,-size, 0.0f, 1.0f, 0.0f,
		-size, size, 0.0f, 0.0f, 1.0f,
		-size,-size, 0.0f, 0.0f, 0.0f,

		 size,-size, 0.0f, 1.0f, 0.0f,
		 size, size, 0.0f, 1.0f, 1.0f,
		-size, size, 0.0f, 0.0f, 1.0f
	};

	glGenVertexArrays(1, &this->glVAO_quad_dir);
	glGenBuffers(1, &(this->glVBO_quad_dir));
	glBindVertexArray(this->glVAO_quad_dir);
	glBindBuffer(GL_ARRAY_BUFFER, this->glVBO_quad_dir);
	glBufferData(GL_ARRAY_BUFFER, (this->glVBO_quad.size()) * sizeof(GLfloat), &(this->glVBO_quad[0]), GL_STATIC_DRAW);
	//-- Vertexes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);

	//-- Texture Coords
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glBindVertexArray(0);


	//-- Static Quad 2D Texture Image Based Render
	this->glVBO_quad_init = {
		1,-1, 0.0f, 1.0f, 0.0f,
		-1, 1, 0.0f, 0.0f, 1.0f,
		-1,-1, 0.0f, 0.0f, 0.0f,

		1,-1, 0.0f, 1.0f, 0.0f,
		1, 1, 0.0f, 1.0f, 1.0f,
		-1, 1, 0.0f, 0.0f, 1.0f
	};

	glGenVertexArrays(1, &this->glVAO_quad_dir_init);
	glGenBuffers(1, &(this->glVBO_quad_dir_init));
	glBindVertexArray(this->glVAO_quad_dir_init);
	glBindBuffer(GL_ARRAY_BUFFER, this->glVBO_quad_dir_init);
	glBufferData(GL_ARRAY_BUFFER, (this->glVBO_quad_init.size()) * sizeof(GLfloat), &(this->glVBO_quad_init[0]), GL_STATIC_DRAW);
	//-- Vertexes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);

	//-- Texture Coords
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glBindVertexArray(0);

	initFrameBuffer2DTexture((GLuint)routes->width, (GLuint)routes->height);




	//-- For 3D Image Based Rendering
	generateCube(1.0);
	glGenVertexArrays(1, &(this->glCubeVAO));
	glBindVertexArray(this->glCubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->glCubeVAO);
	glBufferData(GL_ARRAY_BUFFER, (this->glCubeVertices.size()) * sizeof(GLfloat), &(this->glCubeVertices[0]), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	//-- Vertex Coords
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	//-- Texture Coords								
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glBindVertexArray(0);


	//-- For RayCasting
	g_bfTexObj = initFace2DTex((GLuint)getDisplaySize().x, (GLuint)getDisplaySize().y);
	initFrameBufferRayCasting(g_bfTexObj, (GLuint)getDisplaySize().x, (GLuint)getDisplaySize().y);
}

Model::~Model() {

}

void Model::render(Projection* projection, Camera* camera, vector<Light*> *globalLights) {
	this->shaderProgram->enable();
	//-- State machine activate
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	this->drawElements();
	this->shaderProgram->disable();
}

vector<GLfloat> Model::getGLVBO() {
	return this->glVBO;
}

Transformation * Model::getTransformation() {
	return this->transformation;
}

Light * Model::getLight(){
	return this->light;
}

GLuint Model::getGLVBO_dir() {
	return this->glVBO_dir;
}

GLuint Model::getGLVBO_indexes_dir() {
	return this->glVBO_indexes_dir;
}

vector<GLuint> Model::getGLVBO_indexes() {
	return this->glVBO_indexes;
}

GLuint Model::getGLVBO_indexes_size() {
	return this->glVBO_indexes_size;
}

Routes * Model::getRoutes() {
	return this->routes;
}

tvec4<bool> * Model::getShadingVectorBitMap(){
	return &this->shading;
}

bool * Model::getShadingVectorBitMapXCoord_phong(){
	return &(this->shading.x);
}

bool * Model::getShadingVectorBitMapYCoord_blinn() {
	return &(this->shading.y);
}

bool * Model::getShadingVectorBitMapZCoord_oren() {
	return &(this->shading.z);
}

bool * Model::getShadingVectorBitMapWCoord_cook() {
	return &(this->shading.w);
}

tvec2<bool>* Model::getLightningType(){
	return &this->lightningType;
}

bool * Model::getLightningTypeX_frag(){
	return &(this->lightningType.x);
}

bool * Model::getLightningTypeY_vert() {
	return &(this->lightningType.y);
}

bool * Model::getIsReflected(){
	return &this->isReflected;
}

bool * Model::getIsRefracted(){
	return &this->isRefracted;
}

bool * Model::getIsNormalMapped(){
	return &this->isNormalMappedTextured;
}

bool * Model::getIsParallaxMapped(){
	return &this->isParallaxMappedTextured;
}

float * Model::getParallaxMapHeight(){
	return &this->parallaxMapHeight;
}

float * Model::getRefractedIndex(){
	return &this->refractedIndex;
}

void Model::setTransformation(Transformation * transformation) {
	this->transformation = transformation;
}

void Model::setLight(Light * light){
	this->light = light;
}

void Model::setShader(CGLSLProgram * shader){
	this->shaderProgram = shader;
}

void Model::isReflect(bool isReflected){
	this->isReflected = isReflected;
}

void Model::setShadowMapId(const GLuint ShadowMapId){
	this->ShadowMapId = ShadowMapId;
}

void Model::setDepthBiasMVP(const glm::mat4 DepthBiasMVP){
	this->DepthBiasMVP = DepthBiasMVP;
}

void Model::setIsReflected(bool ref){
	this->isReflected = ref;
}

void Model::setIsRefracted(bool ref){
	this->isRefracted = ref;
}

GLuint Model::initFace2DTex(GLuint bfTexWidth, GLuint bfTexHeight){
	GLuint backFace2DTex;
	glGenTextures(1, &backFace2DTex);
	glBindTexture(GL_TEXTURE_2D, backFace2DTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, bfTexWidth, bfTexHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	return backFace2DTex;
}

void Model::initGLDataBinding() {
	this->glVBO_indexes_size = this->glVBO_indexes.size();

	// -- VBO Data
	glGenBuffers(1, &(this->glVBO_dir));
	glBindBuffer(GL_ARRAY_BUFFER, this->glVBO_dir);
	glBufferData(GL_ARRAY_BUFFER, (this->glVBO.size()) * sizeof(GLfloat), &(this->glVBO[0]), GL_STATIC_DRAW);
		// -- Vertexes
		glEnableVertexAttribArray(0);

		// -- Normals
		glEnableVertexAttribArray(1);

		// -- Texture Coord
		glEnableVertexAttribArray(2);

		//-- Tangents
		glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// -- Indexes Data
	glGenBuffers(1, &(this->glVBO_indexes_dir));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->glVBO_indexes_dir);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->glVBO_indexes.size() * sizeof(GLuint), &(this->glVBO_indexes[0]), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//-- Enable Backface Culling and Z Buffer
	/*glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);*/

	this->glVBO.~vector();
	this->glVBO_indexes.~vector();
}

void Model::roundIt(){
	float maxi = glm::max(this->maxVec.x, glm::max(this->maxVec.y, this->maxVec.z));

	vec3 centro;
	centro.x = (this->maxVec.x + this->minVec.x) / 2.0f;
	centro.y = (this->maxVec.y + this->minVec.y) / 2.0f;
	centro.z = (this->maxVec.z + this->minVec.z) / 2.0f;

	for (int i = 0; i < (int)this->glVBO.size(); i+=12){
		this->glVBO[i] = (this->glVBO[i] - centro.x) / maxi;
		this->glVBO[i+1] = (this->glVBO[i+1] - centro.y) / maxi;
		this->glVBO[i+2] = (this->glVBO[i+2] - centro.z) / maxi;
	}

	this->maxVec.x = (this->maxVec.x - centro.x) / 2.0f;
	this->maxVec.y = (this->maxVec.y - centro.y) / 2.0f;
	this->maxVec.z = (this->maxVec.z - centro.z) / 2.0f;

	this->minVec.x = (this->minVec.x - centro.x) / 2.0f;
	this->minVec.y = (this->minVec.y - centro.y) / 2.0f;
	this->minVec.z = (this->minVec.z - centro.z) / 2.0f;
}

void Model::bind(CGLSLProgram * shader){
	//this->light->bind(shader, true);
	//glUniform1f(glGetUniformLocation(shader->getProgramID(), "u_material.shininess"),
	//	(GLfloat)0.5f);

	glUniformMatrix4fv(
		glGetUniformLocation(shader->getProgramID(), "u_model_matrix"), 1, GL_FALSE, &(this->transformation->getTransformMatrix())[0][0]);
}

void Model::render(CGLSLProgram * shader){
	//shader->enable();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//-- Drawing Elements
	//-- VBO Data
	glBindBuffer(GL_ARRAY_BUFFER, this->glVBO_dir);
	//-- Vertex 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), 0);
	//-- Normals								
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	//-- Texture Coord								
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	//-- Tangents								
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (void*)(9 * sizeof(GLfloat)));

	//-- Drawing
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->glVBO_indexes_dir);

	glDrawElements(GL_TRIANGLES, this->glVBO_indexes_size, GL_UNSIGNED_INT, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(0);

	//shader->disable();
}

GLuint Model::createImageColor2DTextureAttachment(const int width, const int height){
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

void Model::initFrameBuffer2DTexture(GLuint texWidth, GLuint texHeight){
	glGenFramebuffers(1, &g_frameBuffer_2D);
	glBindFramebuffer(GL_FRAMEBUFFER, g_frameBuffer_2D);
	
	glGenTextures(1, &a_acum_texture);
	glBindTexture(GL_TEXTURE_2D, a_acum_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, a_acum_texture, 0);
	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers);

	checkFramebufferStatus();

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, (GLsizei)getDisplaySize().x, (GLsizei)getDisplaySize().y);
}

void Model::render2DImagesBased(CGLSLProgram * firstPass, CGLSLProgram * secondPass, CGLSLProgram * thirdPass, CGLSLProgram * test, mat4 view, mat4 proj, vec3 cam_pos, GLuint tff){
	float fFrameCount = (float)this->routes->depth;
	float alpha;
	GLuint* TextureID;
	int size;

	//-- Selecting Case
	vec3 direction = vec3(0.0f) - cam_pos;
	float offset_x = glm::acos(glm::dot(direction, vec3(1.0, 0.0, 0.0)) / (glm::length(direction) * glm::length(vec3(1.0, 0.0, 0.0))));
	float offset_y = glm::acos(glm::dot(direction, vec3(0.0, 1.0, 0.0)) / (glm::length(direction) * glm::length(vec3(0.0, 1.0, 0.0))));
	float offset_z = glm::acos(glm::dot(direction, vec3(0.0, 0.0, 1.0)) / (glm::length(direction) * glm::length(vec3(0.0, 0.0, 1.0))));
	GLsizei width, height;

	float min = glm::min(offset_x, glm::min(offset_y, offset_z));

	if (min == offset_x) {
		alpha = 2.0f / routes->width;
		size = routes->width;
		TextureID = Texture2D.z;
	} else if (min == offset_y) {
		alpha = 2.0f / routes->height;
		size = routes->height;
		TextureID = Texture2D.y;	
	} else {
		alpha = 2.0f / routes->depth;
		size = routes->depth;
		TextureID = Texture2D.x;
	}

	/*alpha = 2.0f / routes->height;
	size = routes->height;
	TextureID = Texture2D.y;*/

	//transformation->setTraslationMatrix(0.0f, 0.0f, 1.0f);
	glm::vec3 tVectorSaved = transformation->getTraslationVector();

	for (int i = 0; i < size; i++){
		//-- Render first in FBO

		glViewport(0, 0, (GLsizei)getDisplaySize().x, (GLsizei)getDisplaySize().y);
		thirdPass->enable();
		//-- Bindind Stuff
		glUniformMatrix4fv(glGetUniformLocation(thirdPass->getProgramID(), "u_model_matrix"), 1, GL_FALSE, value_ptr(transformation->getTransformMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(thirdPass->getProgramID(), "u_view_matrix"), 1, GL_FALSE, value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(thirdPass->getProgramID(), "u_projection_matrix"), 1, GL_FALSE, value_ptr(proj));

		//-- Enabling Stuff
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TextureID[i]);
		glUniform1i(glGetUniformLocation(thirdPass->getProgramID(), "u_texture_sampler"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_1D, tff);
		glUniform1i(glGetUniformLocation(thirdPass->getProgramID(), "u_transfer_function"), 1);

		glBindVertexArray(this->glVAO_quad_dir);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glDisable(GL_BLEND);
		transformation->increaseTraslationMatrix(0.0f, 0.0f, alpha);
		thirdPass->disable();
	}

	transformation->setTraslationMatrix(tVectorSaved);
}

void Model::MAP_3DTEXT(float TexIndex){
	glTexCoord3f(0.0f, 0.0f, ((float)TexIndex + 1.0f) / 2.0f); 
	glVertex3f(-dOrthoSize, -dOrthoSize, TexIndex); 
	glTexCoord3f(1.0f, 0.0f, ((float)TexIndex + 1.0f) / 2.0f); 
	glVertex3f(dOrthoSize, -dOrthoSize, TexIndex); 
	glTexCoord3f(1.0f, 1.0f, ((float)TexIndex + 1.0f) / 2.0f);  
	glVertex3f(dOrthoSize, dOrthoSize, TexIndex); 
	glTexCoord3f(0.0f, 1.0f, ((float)TexIndex + 1.0f) / 2.0f);  
	glVertex3f(-dOrthoSize, dOrthoSize, TexIndex);
}

void Model::renderWith3DTextureBeginEnd(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.05f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

	glTranslatef(0.5f, 0.5f, 0.5f);
	glScaled((float)routes->width / (float)routes->width,
		-1.0f*(float)routes->width / (float)(float)routes->height,
		(float)routes->width / (float)routes->depth);
	glMultMatrixf(value_ptr(transformation->getTransformMatrix()));
	
	//glMatrixMode(GL_MODELVIEW);
	//glLoadMatrixf(value_ptr(transformation->getTransformMatrix()));

	glEnable(GL_TEXTURE_3D);
	glBindTexture(GL_TEXTURE_3D, Texture3D);
	for (float fIndx = -1.0f; fIndx <= 1.0f; fIndx += 0.01f)
	{
		glBegin(GL_QUADS);
		MAP_3DTEXT(fIndx);
		glEnd();
	}
}

void Model::renderWith3DTexture(CGLSLProgram * shader, mat4 view, mat4 proj){
	shader->enable();
	//-- Bindind Stuff
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "u_model_matrix"), 1, GL_FALSE, value_ptr(transformation->getTransformMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "u_view_matrix"), 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "u_projection_matrix"), 1, GL_FALSE, value_ptr(proj));

	//-- Enabling Stuff
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//-- Binding Texture Stuff
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_3D, Texture3D);
	glUniform1i(glGetUniformLocation(shader->getProgramID(), "u_texture_sampler"), 0);

	//-- Binding Stuff
	glBindVertexArray(glCubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//-- Turn Everything off
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_3D, 0);
	glActiveTexture(0);

	shader->disable();
}

void Model::initVBORayCasting(){
	GLfloat vertices[24] = {
		0.0, 0.0, 0.0,
		0.0, 0.0, 1.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 1.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 1.0,
		1.0, 1.0, 0.0,
		1.0, 1.0, 1.0
	};

	GLuint indices[36] = {
		1,5,7,
		7,3,1,
		0,2,6,
		6,4,0,
		0,1,3,
		3,2,0,
		7,5,4,
		4,6,7,
		2,3,7,
		7,6,2,
		1,0,4,
		4,5,1
	};
	GLuint gbo[2];

	glGenBuffers(2, gbo);
	GLuint vertexdat = gbo[0];
	GLuint veridxdat = gbo[1];
	glBindBuffer(GL_ARRAY_BUFFER, vertexdat);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	// used in glDrawElement()
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, veridxdat);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLuint), indices, GL_STATIC_DRAW);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	// vao like a closure binding 3 buffer object: verlocdat vercoldat and veridxdat
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0); // for vertexloc
	glEnableVertexAttribArray(1); // for vertexcol

								  // the vertex location is the same as the vertex color
	glBindBuffer(GL_ARRAY_BUFFER, vertexdat);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLfloat *)NULL);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLfloat *)NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, veridxdat);
	// glBindVertexArray(0);
	g_vao = vao;
}

void Model::drawBoxRayCasting(GLenum glFaces){
	glEnable(GL_CULL_FACE);
	glCullFace(glFaces);
	glBindVertexArray(g_vao);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)NULL);
	glDisable(GL_CULL_FACE);
}

void Model::bindUniformsRayCasting(CGLSLProgram * shader, GLuint g_tffTexObj){
	GLint screenSizeLoc = glGetUniformLocation(shader->getProgramID(), "ScreenSize");
	if (screenSizeLoc >= 0)
		glUniform2f(screenSizeLoc, getDisplaySize().x, getDisplaySize().y);
	else
		cout << "ScreenSize"
			<< "is not bind to the uniform"
			<< endl;

	GLint stepSizeLoc = glGetUniformLocation(shader->getProgramID(), "StepSize");
	GL_ERROR();
	if (stepSizeLoc >= 0)
		glUniform1f(stepSizeLoc, g_stepSize);
	else

		cout << "StepSize"
			<< "is not bind to the uniform"
			<< endl;
	GL_ERROR();
	GLint transferFuncLoc = glGetUniformLocation(shader->getProgramID(), "TransferFunc");
	if (transferFuncLoc >= 0){
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_1D, g_tffTexObj);
		glUniform1i(transferFuncLoc, 0);
	}
	else{
		cout << "TransferFunc"
			<< "is not bind to the uniform"
			<< endl;
	}
	GL_ERROR();
	GLint backFaceLoc = glGetUniformLocation(shader->getProgramID(), "ExitPoints");
	if (backFaceLoc >= 0){
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, g_bfTexObj);
		glUniform1i(backFaceLoc, 1);
	}
	else{
		cout << "ExitPoints"
			<< "is not bind to the uniform"
			<< endl;
	}
	GL_ERROR();
	GLint volumeLoc = glGetUniformLocation(shader->getProgramID(), "VolumeTex");
	if (volumeLoc >= 0){
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_3D, Texture3D);
		glUniform1i(volumeLoc, 2);
	}
	else{
		cout << "VolumeTex"
			<< "is not bind to the uniform"
			<< endl;
	}
}

GLuint Model::renderFirstPassRayCasting(CGLSLProgram * firstPass, mat4 view, mat4 proj){
	glEnable(GL_DEPTH_TEST);
	GL_ERROR();
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, g_frameBuffer);
	glViewport(0, 0, (GLsizei)getDisplaySize().x, (GLsizei)getDisplaySize().y);
	firstPass->enable();
	renderPassRayCasting(firstPass, GL_FRONT, view, proj);
	firstPass->disable();
	GL_ERROR();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return g_bfTexObj;
}

void Model::renderPassRayCasting(CGLSLProgram * shader, GLenum cullFace, mat4 view, mat4 proj){
	GL_ERROR();
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "u_model_matrix"), 1, GL_FALSE, value_ptr(transformation->getTransformMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "u_view_matrix"), 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "u_projection_matrix"), 1, GL_FALSE, value_ptr(proj));

	//-- Draw Box
	//drawBoxRayCasting(cullFace);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (cullFace == GL_FRONT) glDisable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glCullFace(cullFace);
	glBindVertexArray(glCubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);

	GL_ERROR();
}

void Model::renderWithRayCasting(CGLSLProgram * firstPass, CGLSLProgram * secondPass, mat4 view, mat4 proj, GLuint ttf){
	//-- RayCasting First Pass
	//--g_bfTexObj
	glEnable(GL_DEPTH_TEST);
	GL_ERROR();
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, g_frameBuffer);
	glViewport(0, 0, (GLsizei)getDisplaySize().x, (GLsizei)getDisplaySize().y);
	firstPass->enable();
	renderPassRayCasting(firstPass, GL_FRONT, view, proj);
	firstPass->disable();
	GL_ERROR();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//-- RayCasting Second Pass
	glViewport(0, 0, (GLsizei)getDisplaySize().x, (GLsizei)getDisplaySize().y);
	GL_ERROR();
	secondPass->enable();
	bindUniformsRayCasting(secondPass, ttf);
	renderPassRayCasting(secondPass, GL_BACK, view, proj);
	secondPass->disable();
	GL_ERROR();
	glDisable(GL_DEPTH_TEST);
}

void Model::setg_bfTexObj(GLuint newg_bfTexObj){
	this->g_bfTexObj = newg_bfTexObj;
}

void Model::initFrameBufferRayCasting(GLuint texObj, GLuint texWidth, GLuint texHeight) {
	// create a depth buffer for our framebuffer
	GLuint depthBuffer;
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, texWidth, texHeight);

	// attach the texture and the depth buffer to the framebuffer
	glGenFramebuffers(1, &g_frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, g_frameBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texObj, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
	checkFramebufferStatus();
	//glEnable(GL_DEPTH_TEST);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, (GLsizei)getDisplaySize().x, (GLsizei)getDisplaySize().y);
}

void Model::checkFramebufferStatus() {
	GLenum complete = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (complete != GL_FRAMEBUFFER_COMPLETE){
		cout << "framebuffer is not complete" << endl;
		exit(EXIT_FAILURE);
	}
}