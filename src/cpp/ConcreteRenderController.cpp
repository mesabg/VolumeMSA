#include <ConcreteRenderController.h>

double ConcreteRenderController::lastFrameTime = ConcreteRenderController::getCurrentTime();
double ConcreteRenderController::delta = 0.0f;

ConcreteRenderController::ConcreteRenderController(int width, int height) {
	//-- Initializing complete GUI 
	this->gui = GUI::Instance(this, width, height);
	this->sideBar = SideBar::Instance(this);

	//-- Initializing Stage
	this->stage = Stage::Instance(this);
	this->stage->Notify("initSideBar()", NULL);
	this->stage->Notify("width/height", (void*)(new int[2]{ width, height }));
	this->stage->Notify("initVBOs()", NULL);

	//-- Reshape screen
	this->gui->reshape(this->gui->getWindow(), (int)width, (int)height);
	this->sideBar->reshape((int)width, (int)height);
}

ConcreteRenderController::~ConcreteRenderController() {
	//-- Kill Everything
	this->gui->Destroy();
}

void ConcreteRenderController::Send(string message, void* data, RenderColleague* renderColleague) {
	if (message == "Reshape" && renderColleague == this->gui) {
		this->stage->getProjection()->setAspectRatio(((float*)data)[0] / ((float*)data)[1]);
		this->sideBar->reshape((int)((float*)data)[0], (int)((float*)data)[1]);
	}

	//-- Main Object Initializing
	if (message == "MainObject" && renderColleague == this->stage) {
		this->sideBar->setSelectModelTarget(this->stage->getSelectedModelIndex());
		//this->sideBar->setSelectLightTarget(this->stage->getSelectedLightIndex());
		
	}

	if (message == "tffColor->SideBar" && renderColleague == this->stage) {
		this->sideBar->setTffColor((float*)data);
		this->sideBar->bindPrincipal();
	}

	//-- Event processing
	if (message == "eventKeyPressed" && renderColleague == this->gui)
		this->stage->Notify(message, data);

	if (message == "eventScroll" && renderColleague == this->gui)
		this->stage->Notify(message, data);

	if (message == "mouseButton" && renderColleague == this->gui)
		this->stage->Notify(message, data);

	//-- Options
	if (message == "SendSelectedModelProperties" && renderColleague == this->sideBar)
		this->sideBar->setModel( this->stage->getSelectedModel() );

	if (message == "RenderType" && renderColleague == this->sideBar) 
		this->stage->Notify(message, data);
	/*if (message == "SendSelectedLightProperties" && renderColleague == this->sideBar)
		this->sideBar->setModel( this->stage->getSelectedLight() );*/
}

void ConcreteRenderController::render() {
	glClearColor(0.2f, 0.2f, 0.2f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//-- Render the stage
	this->stage->render();

	//-- Update Side Bar
	this->sideBar->update();
}

double ConcreteRenderController::getCurrentTime(){
	return glfwGetTime()*1000/*/glfwGetTimerValue()*/;
}

double ConcreteRenderController::getFrameTimeSeconds(){
	return delta;
}

int ConcreteRenderController::infinity() {
	while (!glfwWindowShouldClose(this->gui->getWindow())) {
		//-- GUI Buffers Update
		this->gui->activePrimaryWindow();
		glfwPollEvents();
		this->render();
		glfwSwapBuffers(this->gui->getWindow());

		//-- Updating current time
		double currentFrameTime = getCurrentTime();
		delta = (currentFrameTime - lastFrameTime) / 1000.0f;
		lastFrameTime = currentFrameTime;
	}
	return EXIT_SUCCESS;
}

int ConcreteRenderController::finish() {
	this->gui->Destroy();
	this->sideBar->Destroy();
	return EXIT_SUCCESS;
}