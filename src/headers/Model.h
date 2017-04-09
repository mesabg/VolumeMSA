#pragma once
#ifndef __MODEL_H_
#define __MODEL_H_

//- Defines
#define GL_ERROR() checkForOpenGLError(__FILE__, __LINE__)

//-- Global Includes
#include <string>
#include <sstream>
#include <vector>

//-- Class Includes
#include <CGLSLProgram.h>
#include <Camera.h>
#include <Projection.h>
#include <Transformation.h>
#include <Routes.h>
#include <Light.h>
#include <Texture.h>

using glm::vec2;
using glm::tvec2;
using glm::vec3;
using glm::vec4;
using glm::tvec4;
using std::string;
using std::vector;
using std::cout;
using std::endl;

//-- Extern Funcions
extern vec2 getDisplaySize();

//-- Glob Functions
extern int checkForOpenGLError(const char* file, int line);

class Model {
protected:
	//-- Array to VBO
	vector<GLfloat> glVBO, glVBO_quad, glVBO_quad_init;
	GLuint glVBO_dir, glVBO_quad_dir, glVAO_quad_dir;
	GLuint glVBO_quad_dir_init, glVAO_quad_dir_init;
	GLuint glVBO_indexes_dir;
	vector<GLuint> glVBO_indexes;
	GLuint glVBO_indexes_size;
	vec3 minVec, maxVec;
	GLuint textureID;

	//-- Render With Texture 2D
	tvec3<GLuint*> Texture2D;
	GLuint g_frameBuffer_2D;
	GLuint a_acum_texture;
	glm::mat4 modelo, vista, proyeccion;


	//-- Render With Texture 3D
	vector<GLfloat> glCubeVertices;
	vector<GLuint> glCubeIndexes;
	GLuint glCubeVerticesData, glCubeIndexesData, glCubeVAO;
	GLuint Texture3D;
	float dOrthoSize = 1.0f;

	//-- For RayCasting
	float g_stepSize = 0.001f;
	GLuint g_bfTexObj;
	GLuint g_frameBuffer;
	GLuint volumeTexture3D;
	GLuint g_vao;

	//-- Routes
	Routes* routes;

	//-- Shading Program
	CGLSLProgram* shaderProgram;

	//-- Arrays to load a model
	vector<GLfloat*> vertexes;
	vector<GLfloat*> normal;
	vector<GLfloat*> texture_;
	GLfloat max, min;
	int vertexesLenght;

	//-- Structures
	Transformation* transformation;

	//-- Shader Active
	tvec4<bool> shading;
	tvec2<bool> lightningType;

	//--Is reflected
	bool isReflected;
	bool isRefracted;
	float refractedIndex;

	//--
	bool isNormalMappedTextured;
	bool isParallaxMappedTextured;
	float parallaxMapHeight;

	//-- Light material values
	Light* light;
	GLuint ShadowMapId;
	glm::mat4 DepthBiasMVP;

	//-- Uniforms IDs
	vector<GLint> *ID;

	//-- Some functions
	void drawElements();

	void generateCube(GLfloat SIZE);

public:
	Model();
	Model(Routes* routes);
	~Model();
	void render(Projection* projection, Camera* camera, vector<Light*> *globalLights);

	//-- Getters
	vector<GLfloat> getGLVBO();
	Transformation* getTransformation();
	Light* getLight();
	GLuint getGLVBO_dir();
	GLuint getGLVBO_indexes_dir();
	vector<GLuint> getGLVBO_indexes();
	GLuint getGLVBO_indexes_size();
	Routes* getRoutes();
	tvec4<bool>* getShadingVectorBitMap();
	bool* getShadingVectorBitMapXCoord_phong();
	bool* getShadingVectorBitMapYCoord_blinn();
	bool* getShadingVectorBitMapZCoord_oren();
	bool* getShadingVectorBitMapWCoord_cook();
	tvec2<bool>* getLightningType();
	bool* getLightningTypeX_frag();
	bool* getLightningTypeY_vert();
	bool* getIsReflected();
	bool* getIsRefracted();
	bool* getIsNormalMapped();
	bool* getIsParallaxMapped();
	float* getParallaxMapHeight();
	float* getRefractedIndex();

	//-- Setters
	void setTransformation(Transformation* transformation);
	void setLight(Light* light);
	void setShader(CGLSLProgram* shader);
	void isReflect(bool isReflected);
	void setShadowMapId(const GLuint ShadowMapId);
	void setDepthBiasMVP(const glm::mat4 DepthBiasMVP);
	void setIsReflected(bool ref);
	void setIsRefracted(bool ref);

	//-- Functions
	GLuint initFace2DTex(GLuint bfTexWidth, GLuint bfTexHeight);
	void initGLDataBinding();
	void roundIt();
	void bind(CGLSLProgram* shader);
	void render(CGLSLProgram* shader);

	//-- 2D Texture Based Render
	GLuint createImageColor2DTextureAttachment(const int width, const int height);
	void initFrameBuffer2DTexture(GLuint texWidth, GLuint texHeight);
	void render2DImagesBased(CGLSLProgram * firstPass, CGLSLProgram * secondPass, CGLSLProgram * somePass, CGLSLProgram * test, mat4 view, mat4 proj, vec3 cam_pos, GLuint tff);

	//-- 3D Texture Based Render
	void MAP_3DTEXT(float TexIndex);
	void renderWith3DTextureBeginEnd();
	void renderWith3DTexture(CGLSLProgram* shader, mat4 view, mat4 proj);

	//-- Raycasting Functions
	void initVBORayCasting();
	void drawBoxRayCasting(GLenum glFaces);
	void bindUniformsRayCasting(CGLSLProgram* shader, GLuint g_tffTexObj);
	GLuint renderFirstPassRayCasting(CGLSLProgram * firstPass, mat4 view, mat4 proj);
	void renderPassRayCasting(CGLSLProgram* shader, GLenum cullFace, mat4 view, mat4 proj);
	void renderWithRayCasting(CGLSLProgram * firstPass, CGLSLProgram * secondPass, mat4 view, mat4 proj, GLuint ttf);
	void setg_bfTexObj(GLuint newg_bfTexObj);
	void initFrameBufferRayCasting(GLuint texObj, GLuint texWidth, GLuint texHeight);
	void checkFramebufferStatus();
};
#endif
