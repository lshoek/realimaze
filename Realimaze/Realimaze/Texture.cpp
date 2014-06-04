#include <Windows.h>
#include <glut.h>
#include <string>
#include <iostream>
#include <fstream>
#include "stb_image.h"
#include "Texture.h"
#include "Font.h"
#include "Orientation.h"

using namespace std;
typedef map<char, Glyph>::iterator cgmap;
unsigned char* image;
const char* filename;
int* width;
int* height;

Texture::Texture(const string fname)
{
	filename = fname.c_str();
	stbi_uc* img = stbi_load(filename, &width, &height, NULL, 4);
	image = img;
	cout << "> " << filename << " loaded" << endl;
}

Texture::Texture(IplImage *img)
{
	ConvertIplToTexture(img);
}

Texture::~Texture()
{}

void Texture::ConvertIplToTexture(IplImage *image)
{
	cvCvtColor(image, image, CV_BGR2RGB);
	cvFlip(image, NULL, 0);
	GLuint t;
	glGenTextures(1, &t);
	glBindTexture(GL_TEXTURE_2D, t);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image->width, image->height, GL_RGB, GL_UNSIGNED_BYTE, image->imageData);
	textureId = t;
}

GLuint Texture::getTextureId()
{
	if (textureId == 0)
	{
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D,
			0,					//level
			GL_RGBA,			//internal format
			width,				//width
			height,				//height
			0,					//border
			GL_RGBA,			//data format
			GL_UNSIGNED_BYTE,	//data type
			image);				//data
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	return textureId;
}
