#pragma once

#include "Orientation.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\objdetect\objdetect.hpp>
#include <cv.h>
#include <iostream>
#include <stdio.h>
#include "globaldefines.h"

using namespace cv;

class PosF
{
public:
	float xPos, yPos;
	PosF(float xP, float yP) { xPos = xP; yPos = yP; };
	PosF() { xPos = 0; yPos = 0; };
	~PosF() {};
	void setPos(float xP, float yP) { xPos = xP; yPos = yP; };
};

class Orientation
{
public:
	PosF orientPos{ SCRN_WIDTH / 2, SCRN_HEIGHT / 2 }, centerPos{ 53, 70 };
	float boundary = 100;

	Orientation();
	~Orientation();
	PosF getOrientationFactor();
	string getVars();
	void modifyImage();
	IplImage* getVideoImage();
	Point getMiddlePointLocation();
	void releaseImageData();
};
