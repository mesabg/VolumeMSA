#include <TransferFunction.h>

bool TransferFunction::comparePoints(ControlPoint a, ControlPoint b){
	return a.getPosition().x < b.getPosition().x;
}

void TransferFunction::orderPoints(){
	//-- Bubble Sort Ordering
	unsigned int n = control_points.size();
	for (unsigned int i = 0; i < n -1 ; i++)
		for (unsigned int j = 0; j < n - i - 1; j++)
			if (control_points[j]->getPosition().x > control_points[j + 1]->getPosition().x)
				swap(&control_points[j], &control_points[j+1]);
}

void TransferFunction::swap(ControlPoint** a, ControlPoint** b){
	ControlPoint* aux = new ControlPoint(*(*a));
	*(a) = *(b);
	*(b) = aux;
}

float TransferFunction::divideDifference(int x0, int x1, int fx0, int fx1){
	x0++; x1++; fx0++; fx1++;
	return float(fx1-fx0)/float(x1-x0);
}

void TransferFunction::linearInterpolation(){
	//-- reset values
	for (unsigned int i = 0; i < length; i++) {
		texture_dataLinearSpline[i * 4 + 0] = 0;
		texture_dataLinearSpline[i * 4 + 1] = 0;
		texture_dataLinearSpline[i * 4 + 2] = 0;
		texture_dataLinearSpline[i * 4 + 3] = 0;
	}

	double partial_length;
	double alpha_factor, r_factor, g_factor, b_factor;
	double displacement = double(1) / double(this->length);
	unsigned int step, step_acum = 0, index = 0;

	unsigned int x, x0, x1;
	unsigned int B0;
	float r_B0, g_B0, b_B0, a_B0;
	float r_B1, g_B1, b_B1, a_B1;
	unsigned int steps2interpolate;
	
	for (unsigned int i = 0; i < control_points.size()-1; i++){
		partial_length = control_points[i + 1]->getPosition().x - control_points[i]->getPosition().x;
		step = unsigned int(this->length * partial_length);
		step_acum += step;
		if (i == control_points.size() - 2) step += (this->length - step_acum);
		
		//-- Getting X's
		x0 = control_points[i]->getPosition().x;
		x1 = control_points[i+1]->getPosition().x;

		//-- Getting B0's
		r_B0 = float(control_points[i]->getColor().r);
		g_B0 = float(control_points[i]->getColor().g);
		b_B0 = float(control_points[i]->getColor().b);
		a_B0 = float(control_points[i]->getPosition().y);

		//-- Getting B1's
		r_B1 = divideDifference(x0, x1, control_points[i]->getColor().r, control_points[i + 1]->getColor().r);
		g_B1 = divideDifference(x0, x1, control_points[i]->getColor().g, control_points[i + 1]->getColor().g);
		b_B1 = divideDifference(x0, x1, control_points[i]->getColor().b, control_points[i + 1]->getColor().b);
		a_B1 = divideDifference(x0, x1, control_points[i]->getPosition().y, control_points[i + 1]->getPosition().y);

		//-- Push x0 value, and x1 value
		//-- x0
		texture_dataLinearSpline[x0 * 4 + 0] = float(control_points[i]->getColor().r) / float(length - 1);
		texture_dataLinearSpline[x0 * 4 + 1] = float(control_points[i]->getColor().g) / float(length - 1);
		texture_dataLinearSpline[x0 * 4 + 2] = float(control_points[i]->getColor().b) / float(length - 1);
		texture_dataLinearSpline[x0 * 4 + 3] = float(control_points[i]->getPosition().y) / float(length - 1);
		//-- x1
		texture_dataLinearSpline[x1 * 4 + 0] = float(control_points[i+1]->getColor().r) / float(length - 1);
		texture_dataLinearSpline[x1 * 4 + 1] = float(control_points[i+1]->getColor().g) / float(length - 1);
		texture_dataLinearSpline[x1 * 4 + 2] = float(control_points[i+1]->getColor().b) / float(length - 1);
		texture_dataLinearSpline[x1 * 4 + 3] = float(control_points[i+1]->getPosition().y) / float(length - 1);

		for (unsigned int j = x0 + 1; j < x1; j++){
			//-- Steps to be interpolated (x0 && x1 are already known)
			texture_dataLinearSpline[j * 4 + 0] = float(int(r_B0 + r_B1*(float(j - x0)))) / float(length - 1);
			texture_dataLinearSpline[j * 4 + 1] = float(int(g_B0 + g_B1*(float(j - x0)))) / float(length - 1);
			texture_dataLinearSpline[j * 4 + 2] = float(int(b_B0 + b_B1*(float(j - x0)))) / float(length - 1);
			texture_dataLinearSpline[j * 4 + 3] = float(int(a_B0 + a_B1*(float(j - x0)))) / float(length - 1);
		}
	}

	/*for (unsigned int i = 0; i < length; i++) {
		cout << "R :: " << texture_dataLinearSpline[i * 4 + 0];
		cout << " G :: " << texture_dataLinearSpline[i * 4 + 1];
		cout << " B :: " << texture_dataLinearSpline[i * 4 + 2];
		cout << " A :: " << texture_dataLinearSpline[i * 4 + 3] << endl;
	}
	system("pause");*/
}

void TransferFunction::cuadraticInterpolation(){
}

void TransferFunction::cubicInterpolations(){
}

TransferFunction::TransferFunction(unsigned int length):length(length){
	//-- Init first 2 points on the array
	//cout << "TransferFunction (Constructor)\n";
	this->control_points.push_back(new ControlPoint(tvec2<int>(0, 0), tvec3<int>(0, 0, 0), length));
	//this->control_points.push_back(new ControlPoint(tvec2<int>(225, 100), tvec3<int>(255, 255, 255), length));
	this->control_points.push_back(new ControlPoint(tvec2<int>(255, 255), tvec3<int>(255, 255, 255), length));
	//this->control_points.push_back(new ControlPoint(tvec2<int>(60, 25), tvec3<int>(0, 255, 255), length));
	//this->control_points.push_back(new ControlPoint(tvec2<int>(22, 200), tvec3<int>(255, 0, 0), length));
	this->controlPointSelected = NULL;

	//-- Init texture unit
	internalPixelFormat = GL_RGBA8;
	if (length = 65536) internalPixelFormat = GL_RGBA16;

	glGenTextures(1, &this->texture_unit);
	glBindTexture(GL_TEXTURE_1D, this->texture_unit);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage1D(GL_TEXTURE_1D, 0, internalPixelFormat, length, 0, GL_RGBA, GL_FLOAT, NULL);
	glBindTexture(GL_TEXTURE_1D, 0);

	this->texture_dataLinearSpline = new GLfloat[length * 4];
	this->texture_dataCuadraticSpline = new GLfloat[length * 4];
	this->texture_dataCubicSpline = new GLfloat[length * 4];
	this->orderPoints();
	this->linearInterpolation();


	//-- Initializing Drawing Structure
	//-- Alpha selector structure
	vec2 min = vec2(0.51383838f, 0.93939393f);
	vec2 max = vec2(0.94444444f, 0.51515151f);
	zeroZero = vec2(0.53999988f, 0.559596f);
	oneOne = vec2(0.933333f, 0.91999999);

	this->gl_quad = {
		max.x, min.y, 0.0f, 1.0f, 0.0f,
		min.x, max.y, 0.0f, 0.0f, 1.0f,
		min.x, min.y, 0.0f, 0.0f, 0.0f,

		max.x, min.y, 0.0f, 1.0f, 0.0f,
		max.x, max.y, 0.0f, 1.0f, 1.0f,
		min.x, max.y, 0.0f, 0.0f, 1.0f
	};

	glGenVertexArrays(1, &this->glVAO_quad_dir);
	glGenBuffers(1, &(this->glVBO_quad_dir));
	glBindVertexArray(this->glVAO_quad_dir);
	glBindBuffer(GL_ARRAY_BUFFER, this->glVBO_quad_dir);
	glBufferData(GL_ARRAY_BUFFER, (this->gl_quad.size()) * sizeof(GLfloat), &(this->gl_quad[0]), GL_STATIC_DRAW);

	//-- Vertexes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);

	//-- Texture Coords
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glBindVertexArray(0);

	alpha_selector_texture = new Texture("../textures/transfer_function/axis.jpg");

	alpha_selector_shader = new CGLSLProgram();
	alpha_selector_shader->loadShader("../src/shaders/alpha_selector.vert", CGLSLProgram::VERTEX);
	alpha_selector_shader->loadShader("../src/shaders/alpha_selector.frag", CGLSLProgram::FRAGMENT);
	alpha_selector_shader->create_link();

	//-- init default color
	color = new float[3];
	color[0] = 1.0f;
	color[1] = 1.0f;
	color[2] = 1.0f;
}

TransferFunction::~TransferFunction() {
	this->control_points.~vector();
}

void TransferFunction::pushControlPoint(ControlPoint* controlPoint){
	this->control_points.push_back(new ControlPoint(*(controlPoint)));
	this->orderPoints();
	this->linearInterpolation();
	delete controlPoint;
}

bool TransferFunction::popControlPoint(vec2 controlPointPosition){
	vector<ControlPoint*>::iterator lower; /*= lower_bound(
		control_points.begin(), 
		control_points.end(), 
		new ControlPoint(controlPointPosition), comparePoints);*/
	unsigned int index = (lower - control_points.begin());
	vector<ControlPoint*>::iterator it = control_points.erase(control_points.begin() + index);
	return it._Ptr != NULL;
}

bool TransferFunction::popControlPoint(unsigned int index){
	vector<ControlPoint*>::iterator it = this->control_points.erase(this->control_points.begin()+index);
	return it._Ptr != NULL;
}

void TransferFunction::bindLinearInterpolationTexture(){
	//-- Interpolate to generate data
	glBindTexture(GL_TEXTURE_1D, this->texture_unit);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage1D(GL_TEXTURE_1D, 0, internalPixelFormat, length, 0, GL_RGBA, GL_FLOAT, texture_dataLinearSpline);
	glBindTexture(GL_TEXTURE_1D, 0);
}

GLuint TransferFunction::getTextureUnit(){
	return this->texture_unit;
}

float * TransferFunction::getColor(){
	return color;
}

bool TransferFunction::isClicked(){
	vec2 mousePos = getMousePosition();
	int mouseLeftState = getMouseLeftState();
	int mouseRightState = getMouseRightState();

	if (
		(mousePos.x >= zeroZero.x && mousePos.y <= oneOne.x &&
			mousePos.y >= zeroZero.y && mousePos.y <= oneOne.y &&
			(mouseLeftState == GLFW_PRESS || mouseRightState == GLFW_PRESS))
		) return true;
	
	return false;
}

void TransferFunction::reshape(){
	projection = glm::perspective(45.0f, (float)getDisplaySize().x / (float)getDisplaySize().y, 0.1f, 1000.0f);
}

void TransferFunction::update(){
	vec3 color_transformed = vec3(255 * color[0], 255 * color[1], 255 * color[2]);

	if (!isClicked()) {
		lastMouseLeftState = getMouseLeftState();
		lastMouseRightState = getMouseRightState();
		if (controlPointSelected != NULL) {
			controlPointSelected->setColor(color_transformed);
			this->linearInterpolation();
		}
		return;
	}
	//-- Conversion first
	//-- Necesary Variables
	int mouseLeftState = getMouseLeftState();
	int mouseRightState = getMouseRightState();
	vec2 point = getMousePosition();
	int a = 0, b = 255;
	vec2 factor = vec2(b - a, b - a);
	vec2 scale_x = vec2(zeroZero.x, oneOne.x);
	vec2 scale_y = vec2(zeroZero.y, oneOne.y);

	//-- Calculating
	point.x = (factor.x*(point.x - scale_x.x) / (scale_x.y - scale_x.x)) + a;
	point.y = (factor.y*(point.y - scale_y.x) / (scale_y.y - scale_y.x)) + a;

	if (controlPointSelected != NULL && mouseLeftState == GLFW_PRESS) {
		controlPointSelected->setColor(color_transformed);
		controlPointSelected->setX(int(point.x));
		controlPointSelected->setY(int(point.y));
		this->orderPoints();
		this->linearInterpolation();
		return;
	}

	//-- Checking if a point is clicked (move, select)
	int index = 0;
	for each (ControlPoint* controlPoint in control_points) {
		if (controlPoint->clicked(tvec2<int>(int(point.x), int(point.y))) && mouseRightState == GLFW_PRESS) {
			controlPointSelected = controlPoint;

			for each (ControlPoint* thePoint in control_points) thePoint->setState(false);
			controlPoint->setState(true);

			return;
		}
		index++;
	}

	//-- If it is not clicked, add a new point
	//-- Adding new point
	if (mouseRightState == GLFW_PRESS) {
		for each (ControlPoint* thePoint in control_points) thePoint->setState(false);
		this->control_points.push_back(new ControlPoint(tvec2<int>(int(point.x), int(point.y)), tvec3<int>(int(color_transformed.r), int(color_transformed.g), int(color_transformed.b)), length));
		this->orderPoints();
		this->linearInterpolation();
	}
}

void TransferFunction::draw() {
	alpha_selector_shader->enable();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, alpha_selector_texture->getID());
	glUniform1i(alpha_selector_shader->getLocation("alpha_selector_texture"), 0);
	glBindVertexArray(glVAO_quad_dir);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	alpha_selector_shader->disable();

	//-- Variables to draw
	vec2 point;
	vec2 factor = vec2(oneOne.x - zeroZero.x, oneOne.y - zeroZero.y);
	vec2 scale = vec2(0, 1);

	vector<vec2> points;

	//-- Calculating
	for each (ControlPoint* controlPoint in control_points){
		point = controlPoint->getPositionConvertedZeroOne();
		point.x = (factor.x*(point.x - scale.x) / (scale.y - scale.x)) + zeroZero.x;
		point.y = (factor.y*(point.y - scale.x) / (scale.y - scale.x)) + zeroZero.y;
		points.push_back(point);
	}
	
	//-- Draw Line Strip
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(2.0f);
	glBegin(GL_LINE_STRIP);
	for each (vec2 point in points)
		glVertex2f(point.x, point.y);
	glEnd();

	//-- Draw Points
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(7.5f);
	glBegin(GL_POINTS);
	for (unsigned int i = 0; i < control_points.size(); i++) {
		if (control_points[i]->isActive()) glColor3f(0.0f, 0.8f, 0.0f);
		else glColor3f(0.6f, 0.6f, 0.6f);
		glVertex2f(points[i].x, points[i].y);
	}
	glEnd();
}
