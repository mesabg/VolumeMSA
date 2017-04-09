#include <Stage.h>
#include <iostream>

using namespace std;

Stage* Stage::uniqueStage = NULL;

Stage::Stage(RenderController* renderController) :RenderColleague(renderController) {
	this->initGLSLPrograms();
	//-- Init local structures
	this->projection = new Projection();

	//-- Initialize default values
	this->selectedModel = new float;
	*(this->selectedModel) = -1.0f;
	this->selectedLight = new float;
	*(this->selectedLight) = -1.0f;

	displayType = new int;
	*(displayType) = 0;

	//-- Models Loading
	vector<Routes*> modelsRoutes;
	vector<Transformation*> modelsTransform;

	modelsRoutes.push_back(new Routes(
		/*RAW File*/	"../models/8b/foot_8_256_256_256.raw",
		/*Width*/		256,
		/*Height*/		256,
		/*Depth*/		256,
		/*Bytes*/		1
	));
	modelsTransform.push_back(new Transformation(
		/*Scale*/			1.0f,
		/*Position*/		glm::vec3(0.0f, 0.0f, 0.0f),
		/*Angle*/			0.0f,
		/*Rot Direction*/	glm::vec3(0.0f, 1.0f, 0.0f)
	));


	//-- Init Render Facade
	this->renderFacade = new RenderFacade();
	this->renderFacade->initModelEntities(modelsRoutes, modelsTransform);

	//-- Initializing Player
	this->camera = new Camera(this->renderFacade->getModel(0)->getTransformation());

	//-- Bindind data to render facade
	this->renderFacade->bindShaderPrograms(this->illuminationPrograms);
	this->renderFacade->bindCamera(this->camera);
	this->renderFacade->bindProjection(this->projection);
}

Stage::~Stage() {
	this->camera->~Camera();
	this->projection->~Projection();
}

void Stage::frontRender(){
	//-- Move Camera
	if (!this->renderFacade->ttfClicked())
		this->camera->move();

	//-- Display
	if (*(displayType) == 0) this->renderFacade->render2DImageBased("2DTextureRender_Init", "2DTextureRender_a", "2DTextureRender", "2DTextureRender_Test");
	else if (*(displayType) == 2) this->renderFacade->renderRayCasting("RayCasting_BackFace", "RayCasting");

	this->renderFacade->renderTTF();
}

void Stage::initGLSLPrograms(){
	//-- Graphic Card Info
	GLint texture_size;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &texture_size);
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "Max Texture Size: " << texture_size << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	
	//-- Structure to initialize
	this->illuminationPrograms = new map<string, CGLSLProgram*>();
	vector< map<string, string>* > *routes = new vector< map<string, string>* >({

		//-- For 2D Axis Aligned
		new map<string, string>(
		{ 
			{ "name", "2DTextureRender_a" },
			{ "vertex", "../src/shaders/2DTextureRender_a.vert" }, 
			{ "geometry", "" }, 
			{ "fragment", "../src/shaders/2DTextureRender_a.frag" } 
		}),

		new map<string, string>(
		{
			{ "name", "2DTextureRender" },
			{ "vertex", "../src/shaders/2DTextureRender.vert" },
			{ "geometry", "" },
			{ "fragment", "../src/shaders/2DTextureRender.frag" }
		}),

		new map<string, string>(
		{
			{ "name", "2DTextureRender_Init" },
			{ "vertex", "../src/shaders/2DTextureRender_Init.vert" },
			{ "geometry", "" },
			{ "fragment", "../src/shaders/2DTextureRender_Init.frag" }
		}),

		new map<string, string>(
		{
			{ "name", "2DTextureRender_Test" },
			{ "vertex", "../src/shaders/flat.vert" },
			{ "geometry", "" },
			{ "fragment", "../src/shaders/flat.frag" }
		}),

		//-- For 3D Viewport Aligned
		new map<string, string>(
		{
			{ "name", "3DTextureRender" },
			{ "vertex", "../src/shaders/3DTextureRender.vert" },
			{ "geometry", "" },
			{ "fragment", "../src/shaders/3DTextureRender.frag" }
		}),

		//-- For RayCasting
		new map<string, string>(
		{
			{ "name", "RayCasting_BackFace" },
			{ "vertex", "../src/shaders/backface.vert" },
			{ "geometry", "" },
			{ "fragment", "../src/shaders/backface.frag" }
		}),

		new map<string, string>(
		{
			{ "name", "RayCasting" },
			{ "vertex", "../src/shaders/raycasting.vert" },
			{ "geometry", "" },
			{ "fragment", "../src/shaders/raycasting.frag" }
		})
	});

	//-- Initialize Shader Programs
	std::vector< map<string, string>* >::iterator programRoute;
	for (programRoute = routes->begin(); programRoute != routes->end(); programRoute++){
		std::cout << "\nLoading " << (*programRoute)->at("name") << " shading program...\n";

		this->illuminationPrograms->insert_or_assign(
			(*programRoute)->at("name"),
			new CGLSLProgram()
		);


		this->illuminationPrograms->at( (*programRoute)->at("name") )->loadShader(
			(*programRoute)->at("vertex"),
			CGLSLProgram::VERTEX
		);

		//-- Loading Geometry shader if its possible
		if ((*programRoute)->at("geometry") != "") {
			this->illuminationPrograms->at((*programRoute)->at("name"))->loadShader(
				(*programRoute)->at("geometry"),
				CGLSLProgram::GEOMETRY
			);
		}

		this->illuminationPrograms->at((*programRoute)->at("name"))->loadShader(
			(*programRoute)->at("fragment"),
			CGLSLProgram::FRAGMENT
		);

		this->illuminationPrograms->at((*programRoute)->at("name"))->create_link();
	}
}

Stage * Stage::Instance(RenderController * renderController) {
	if (!uniqueStage)
		uniqueStage = new Stage(renderController);
	return uniqueStage;
}

void Stage::Destroy() {
	if (!uniqueStage) return;
	uniqueStage->~Stage();
}

Projection * Stage::getProjection() {
	return this->projection;
}

Model * Stage::getSelectedModel(){
	return this->renderFacade->getModel(unsigned int(*(this->selectedModel)));
}

float * Stage::getSelectedModelIndex(){
	return this->selectedModel;
}

float * Stage::getSelectedLightIndex(){
	return this->selectedLight;
}

void Stage::Notify(string message, void* data) {
/*	if (message == "initVBOs()")
		this->renderFacade->initVBOs();*/

	/*else*/ if (message == "width/height") {
		this->width = ((float*)data)[0];
		this->height = ((float*)data)[1];
	}
	else if (message == "initSideBar()") {
		this->Send("MainObject", (void*)this->renderFacade->getModel(0));
		this->Send("tffColor->SideBar", (void*)this->renderFacade->getTff()->getColor());
	}

	//-- Managing Events
	else if (message == "eventScroll")
		this->camera->calculateZoom( *((int*)data) );
	else if (message == "mouseButton") {
		if (this->renderFacade->ttfClicked()) return;
		if (((int*)data)[0] == GLFW_MOUSE_BUTTON_LEFT && ((int*)data)[1] == GLFW_PRESS && !this->clicked) {
			//-- Save first click
			this->clicked = true;
			this->xPos = ((int*)data)[2];
			this->yPos = ((int*)data)[3];
			this->xPosFirst = this->xPos;
			this->yPosFirst = this->yPos;

			this->camera->calculatePitch(this->yPos);
			this->camera->calculateAngleAroundPlayer(this->xPos);
		}
		else if (((int*)data)[0] == GLFW_MOUSE_BUTTON_LEFT && ((int*)data)[1] == GLFW_PRESS) {
			//-- Updating click values
			this->xPos = this->xPosFirst - ((int*)data)[2];
			this->yPos = this->yPosFirst - ((int*)data)[3];
			this->camera->calculatePitch(this->yPos);
			this->camera->calculateAngleAroundPlayer(this->xPos);
		}
		else if (((int*)data)[0] == GLFW_MOUSE_BUTTON_LEFT && ((int*)data)[1] == GLFW_RELEASE) {
			//-- Key released
			this->clicked = false;
		}
	}
	else if (message == "RenderType") {
		this->displayType = (int*)data;
	}
}

void Stage::render() {
	this->frontRender();
}
