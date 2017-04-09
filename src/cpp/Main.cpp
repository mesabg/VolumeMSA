#include <Main.h>

int main() {
	ConcreteRenderController* renderController = new ConcreteRenderController();
	renderController->infinity();
	renderController->finish();
}

float getFrameTimeSeconds() {
	return (float)ConcreteRenderController::getFrameTimeSeconds();
}

vec2 getMousePosition() {
	return Mouse::getPosition();
}

int getMouseLeftState(){
	return Mouse::getLeftState();
}

int getMouseRightState(){
	return Mouse::getRightState();
	return 0;
}

vec2 getDisplaySize() {
	return vec2(GUI::getWidth(), GUI::getHeight());
}

int checkForOpenGLError(const char* file, int line) {
	// return 1 if an OpenGL error occured, 0 otherwise.
	/*GLenum glErr;
	int retCode = 0;

	glErr = glGetError();
	while (glErr != GL_NO_ERROR)
	{
		cout << "glError in file " << file
			<< "@line " << line << endl;
		retCode = 1;
		exit(EXIT_FAILURE);
	}
	return retCode;*/
	return 0;
}