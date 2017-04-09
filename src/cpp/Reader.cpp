#include <Reader.h>
#include <iostream>
typedef unsigned char byte;

Reader::Reader(Routes* routes):Model(routes) {
	std::cout << routes->raw_model << endl;

	//-- Reading File
	FILE* pFile;
	pFile = fopen(routes->raw_model.c_str(), "rb");
	if (pFile == NULL) {
		printf("Error reading the file.");
		exit(0);
	}

	int index_reader = 0;
	char imageByte;
	char *image3DTexture = new char[routes->width * routes->height * routes->depth];

	//-- Initialize Array
	char ***Image3D;
	Image3D = new char**[routes->depth];
	/*for (int i = 0; i < routes->depth; i++) {
		Image3D[i] = new char*[routes->width];
		for (int j = 0; j < routes->width; j++)
			Image3D[i][j] = new char[routes->height];
	}*/
	for (int i = 0; i < routes->depth; i++) {
		Image3D[i] = new char*[routes->height];
		for (int j = 0; j < routes->height; j++)
			Image3D[i][j] = new char[routes->width];
	}

	//-- Read Everything
	for (int d = 0; d < routes->depth; d++)
		for (int h = 0; h < routes->height; h++)
			for (int w = 0; w < routes->width; w++){
				fscanf(pFile, "%c", &Image3D[d][h][w]);
				image3DTexture[index_reader] = Image3D[d][h][w];
				index_reader++;
			}
	
	
	//-- Store 3D Texture
	glGenTextures(1, &Texture3D);

	glBindTexture(GL_TEXTURE_3D, Texture3D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	glTexImage3D(GL_TEXTURE_3D, 0, GL_INTENSITY, routes->width, routes->height, routes->depth, 0,
		GL_LUMINANCE, GL_UNSIGNED_BYTE, image3DTexture);
	glBindTexture(GL_TEXTURE_3D, 0);


	this->Texture2D.x = new GLuint[routes->depth];
	this->Texture2D.y = new GLuint[routes->height];
	this->Texture2D.z = new GLuint[routes->width];
	glGenTextures(routes->depth, (GLuint*)this->Texture2D.x);
	glGenTextures(routes->height, (GLuint*)this->Texture2D.y);
	glGenTextures(routes->width, (GLuint*)this->Texture2D.z);

	//-- Building Sets
	char* imageSet_1 = new char[routes->width*routes->height];
	char* imageSet_2 = new char[routes->depth*routes->width];
	char* imageSet_3 = new char[routes->depth*routes->height];

	//-- Set 1
	int index = 0;
	for (int d = 0; d < routes->depth; d++) {
		for (int h = 0; h < routes->height; h++)
			for (int w = 0; w < routes->width; w++){
				imageSet_1[index] = Image3D[d][h][w];
				index++;
			}

		//-- Bind Texture
		glBindTexture(GL_TEXTURE_2D, Texture2D.x[d]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_INTENSITY, routes->height, routes->width, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, (GLvoid*)imageSet_1);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		index = 0;
	}

			

	//-- Set 2 height
	index = 0; 
	for (int h = 0; h < routes->height; h++) {
		for (int w = 0; w < routes->width; w++)
			for (int d = 0; d < routes->depth; d++) {
				imageSet_2[index] = Image3D[d][h][w];
				index++;
			}

		//-- Bind Texture
		glBindTexture(GL_TEXTURE_2D, Texture2D.y[h]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_INTENSITY, routes->depth, routes->width, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, (GLvoid*)imageSet_2);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		index = 0;
	}




	//-- Set 3 width
	index = 0; 
	for (int w = 0; w < routes->width; w++) {
		for (int h = 0; h < routes->height; h++)
			for (int d = 0; d < routes->depth; d++) {
				imageSet_3[index] = Image3D[d][h][w];
				index++;
			}

		//-- Bind Texture
		glBindTexture(GL_TEXTURE_2D, Texture2D.z[w]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_INTENSITY, routes->depth, routes->height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, (GLvoid*)imageSet_3);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		index = 0;
	}

	delete[] image3DTexture;
	delete[] imageSet_1;
	delete[] imageSet_2;
	delete[] imageSet_3;
	delete[] Image3D;
	fclose(pFile);



	//-- Reading volumeTexture3D for RayCasting
	//volumeTexture3D = initVol3DTex(routes->raw_model.c_str(), routes->width, routes->height, routes->depth);
}

Reader::~Reader() {

}

GLuint Reader::initVol3DTex(const char * filename, GLuint w, GLuint h, GLuint d){
	FILE *fp;
	size_t size = w * h * d;
	GLubyte *data = new GLubyte[size];			  // 8bit
	if (!(fp = fopen(filename, "rb")))
	{
		cout << "Error: opening .raw file failed" << endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		cout << "OK: open .raw file successed" << endl;
	}
	if (fread(data, sizeof(char), size, fp) != size)
	{
		cout << "Error: read .raw file failed" << endl;
		exit(1);
	}
	else
	{
		cout << "OK: read .raw file successed" << endl;
	}
	fclose(fp);

	GLuint g_volTexObj;
	glGenTextures(1, &g_volTexObj);
	// bind 3D texture target
	glBindTexture(GL_TEXTURE_3D, g_volTexObj);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
	// pixel transfer happens here from client to OpenGL server
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage3D(GL_TEXTURE_3D, 0, GL_INTENSITY, w, h, d, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);

	delete[]data;
	cout << "volume texture created" << endl;
	return g_volTexObj;
}
