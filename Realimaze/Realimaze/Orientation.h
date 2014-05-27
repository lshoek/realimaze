#pragma once

#include "Orientation.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\objdetect\objdetect.hpp>
#include <cv.h>
#include <iostream>
#include <stdio.h>

using namespace cv;

class Orientation
{

	public:
		Orientation();
		~Orientation();
		void modifyImage();
		void runCamera();
		Mat getVideoImage();
};

