#include <RenderFacade.h>

void RenderFacade::checkAssertions(){
	assert(this->shaders != NULL && "No shaders loaded, load shaders first");
	assert(this->model_entities.size() != 0 && "No models loaded, load some models first");
	assert(this->camera != NULL && "No camera loaded, load a camera first");
	assert(this->projection != NULL && "No projection loaded, load a projection first");
}

RenderFacade::RenderFacade(){
	this->shaders = NULL;
	this->projection = NULL;
	this->camera = NULL;
	TFF8Bytes = new TransferFunction();
	//TFF16Bytes = new TransferFunction(65536);
}

RenderFacade::~RenderFacade(){

}

void RenderFacade::initModelEntities(
	const vector<Routes*> routes, 
	const vector<Transformation*> transformations){
	g_tffTexObj = initTFF1DTex("../models/ttf/tff.dat");
	for (int i = 0; i < (int)routes.size(); i++) {
		this->model_entities.push_back(new Reader(routes[i]));
		this->model_entities.back()->setTransformation(transformations[i]);
	}
}

GLuint RenderFacade::initTFF1DTex(const char * filename){
	// read in the user defined data of transfer function
	ifstream inFile(filename, ifstream::in);
	if (!inFile)
	{
		cout << "Error openning file: " << filename << endl;
		exit(EXIT_FAILURE);
	}

	const int MAX_CNT = 10000;
	GLubyte *tff = (GLubyte *)calloc(MAX_CNT, sizeof(GLubyte));
	inFile.read(reinterpret_cast<char *>(tff), MAX_CNT);
	if (inFile.eof())
	{
		size_t bytecnt = inFile.gcount();
		*(tff + bytecnt) = '\0';
		cout << "bytecnt " << bytecnt << endl;
	}
	else if (inFile.fail())
	{
		cout << filename << "read failed " << endl;
	}
	else
	{
		cout << filename << "is too large" << endl;
	}
	GLuint tff1DTex;
	glGenTextures(1, &tff1DTex);
	glBindTexture(GL_TEXTURE_1D, tff1DTex);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA8, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, tff);
	free(tff);
	return tff1DTex;
}

void RenderFacade::bindProjection(Projection * projection){
	this->projection = projection;
}

void RenderFacade::bindCamera(Camera * camera){
	this->camera = camera;
}

void RenderFacade::bindShaderPrograms(map<string, CGLSLProgram*>* shaders){
	this->shaders = shaders;
}

void RenderFacade::render2DImageBased(string firstPass, string secondPass, string somePass, string testPass){
	this->checkAssertions();

	TFF8Bytes->bindLinearInterpolationTexture();
	GLuint tff = TFF8Bytes->getTextureUnit();

	for (Model* model : this->model_entities) 
		model->render2DImagesBased(
			this->shaders->at(firstPass), 
			this->shaders->at(secondPass), 
			this->shaders->at(somePass),
			this->shaders->at(testPass),
			this->camera->getMatrix(), 
			this->projection->getMatrix(), 
			this->camera->getPosition(),
			/*g_tffTexObj*/tff);
}

void RenderFacade::render(string shaderName){
	this->checkAssertions();

	for (Model* model : this->model_entities) {
		//model->render2DImagesBased(this->shaders->at(shaderName), this->camera->getMatrix(), this->projection->getMatrix(), this->camera->getPosition(), g_tffTexObj);
		//model->renderWith3DTexture(shader, this->camera->getMatrix(), this->projection->getMatrix());
		//model->renderWith3DTextureBeginEnd();
	}
}

void RenderFacade::renderRayCasting(string firstPass, string secondPass) {
	this->checkAssertions();
	CGLSLProgram* shaderfirstPass = this->shaders->at(firstPass);
	CGLSLProgram* shadersecondPass = this->shaders->at(secondPass);
	TFF8Bytes->bindLinearInterpolationTexture();
	GLuint tff = TFF8Bytes->getTextureUnit();
	GLuint ffRender;
	int i = 0;
	for (Model* model : this->model_entities) {
		//ffRender = model->renderFirstPassRayCasting(shaderfirstPass, this->camera->getMatrix(), this->projection->getMatrix());
		//model->setg_bfTexObj(ffRender);
		model->renderWithRayCasting(shaderfirstPass, shadersecondPass, this->camera->getMatrix(), this->projection->getMatrix(), /*g_tffTexObj*/tff);
	}
}

void RenderFacade::render(Projection * projection, Camera * camera, string shaderName){
	this->checkAssertions();
	CGLSLProgram* shader = this->shaders->at(shaderName);
	shader->enable();
	camera->bind(shader);
	projection->bind(shader);
	for (Model* model : this->model_entities) {
		model->bind(shader);
		model->render(shader);
	}
	for (Model* light : this->light_entities) {
		light->bind(shader);
		light->render(shader);
	}
	shader->disable();
}

Model * RenderFacade::getModel(const int index){
	return this->model_entities.at(index);
}

void RenderFacade::initVBOs(){
	for (Model* model : this->model_entities)
		model->initGLDataBinding();
}

void RenderFacade::renderTTF(){
	//-- if it is 8 or 16 (draw accordingly)
	TFF8Bytes->update();
	TFF8Bytes->draw();
}

bool RenderFacade::ttfClicked(){
	return TFF8Bytes->isClicked();
}

TransferFunction * RenderFacade::getTff(){
	return this->TFF8Bytes;
}
