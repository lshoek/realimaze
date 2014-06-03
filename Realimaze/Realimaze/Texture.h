#pragma once
#include <Windows.h>
#include <glut.h>
#include <string>
#include <iostream>
#include <fstream>
#include "stb_image.h"
#include "Texture.h"
#include "Font.h"

using namespace std;

class Texture
{
private:
	stbi_uc* image;
	const char* filename;
	int width;
	int height;
	GLuint textureId;

public:
	Font font;
	Texture(const string fname);
	~Texture();
	GLuint getTextureId();
};

